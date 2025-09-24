#! /bin/bash

docker_run_arg=()
docker_run_cmd='make -C /VITIS/docsrc github'
DOCKERFILE=docker.dockerfile

while [ $# -gt 0 ]
do
    if [ "$1" = '--' ]
    then
        shift
        docker_run_cmd=''
        break
    elif [ "$1" = "--args" ]
    then
      shift
      docker_run_cmd+=" $1"
      shift
      continue
    elif [ "$1" = "--help" -o "$1" = "-h" ]
    then
      usage
      exit 0
    fi
    docker_run_arg+=("$1")
    shift
done

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
ERROR="${RED}ERROR${NC}"
OK="${GREEN}OK${NC}"

APT=false
which apt &> /dev/null && APT=true

echo_error() {
  echo
  echo "============================================================"
  echo
  echo -e "$ERROR: $@"
}
echo_ok() {
  echo -e "$OK: $@"
}

docker_check() {
  echo
  echo "Testing docker"
  if ! which docker &> /dev/null || ! docker build --help | grep -q -- '--target'
  then
    if which docker &> /dev/null
    then
      echo_error "docker version too old. Please, remove any previous version."
      ! $APT && echo "sudo yum remove docker*"
      echo "Then, try installing the latest version using the command:"
    else
      echo_error "docker command not found. Please, install using the command:"
    fi
      $APT && echo "sudo apt update && sudo apt install -y docker.io"
    ! $APT && echo "curl -fsSL https://get.docker.com/ | sh && sudo systemctl start docker && sudo systemctl enable docker"
    exit 1
  fi

  if ! docker ps &> /dev/null
  then
    if ! ps aux | grep -q dockerd &> /dev/null
    then
      echo_error "docker not running. Please, try the following command"
      echo "sudo systemctl start docker"
      exit 1
    fi
    if [ "$( getent group docker )" = "" ]
    then
      echo_error "docker permission denied. Please, use the following command to have access to docker from your user"
      echo "sudo chmod a+rw /var/run/docker.sock"
      exit 1
    fi
    if getent group docker | grep -q "\b$USER\b"
    then
      echo_error "docker permission denied. Please, don't forget to logout completely from $HOSTNAME (terminate X session) and login again so the group update is taken into account"
      exit 1
    fi
    echo_error "docker permission denied. Please, make sure to be in the docker group. Use the following command, then logout and login again"
      $APT && echo "sudo adduser $USER docker"
    ! $APT && echo "sudo usermod -a -G docker $USER"
    exit 1
  fi
}


docker_build() {

  dockertag=$( basename $DOCKERFILE .dockerfile )
  echo "building docker $dockertag using dockerfile $( basename $DOCKERFILE ) ($DOCKERFILE)"

  if [ "$( id -u )" = "0" ]
  then
    echo_error "Launching doker using root user is not supported, please use a real user"
    exit 1
  fi

  if ! docker build --tag=$dockertag:$UID --build-arg UID=$UID -f $DOCKERFILE .
  then
    echo_error "building docker image."
    echo "Please, review above commands and contact Mipsology for support"
    exit 1
  fi

  echo_ok "docker image built without error"
}


docker_run() {

  # by default we keep the same net host to be able to use open ssh X11 connection
  docker_arg="--net=host"
  # if the X11 is local, we mount also the X11 local sockets
  [ "${DISPLAY:0:1}" = ":" ] && docker_arg="$docker_arg -v /tmp/.X11-unix:/tmp/.X11-unix"
  [ -f $HOME/.Xauthority ] && docker_arg="$docker_arg -v $HOME/.Xauthority:/home/demo/.Xauthority:ro"

  TTY=''
  tty &> /dev/null && TTY='-t'

  echo Running
  docker run --privileged --rm -i $TTY \
    --log-driver none \
    -e QT_X11_NO_MITSHM=1 \
    \
    -e DISPLAY=$DISPLAY \
    -v $PWD/../../:/VITIS \
    $docker_arg \
    \
    "${docker_run_arg[@]}" \
    -w /home/demo \
    $dockertag:$UID ${docker_run_cmd} "$@"
}

cd $( dirname ${BASH_SOURCE[0]} )

docker_check
docker_build
docker_run "$@"
