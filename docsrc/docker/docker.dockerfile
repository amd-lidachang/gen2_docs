
# ===========================================================
# Copyright(C) 2015-2023 Mipsology SAS.  All Rights Reserved.
# ===========================================================

FROM ubuntu:focal as zebra_base

ENV DEBIAN_FRONTEND=noninteractive

# install package dependencies
RUN apt-get update && apt-get install -y \
  libglib2.0-dev \
  libsm-dev \
  libxrender-dev \
  libxext6 \
  python3-pip

RUN apt-get update \
 && apt-get install -y latexmk tex-gyre texlive-latex-extra texlive-extra-utils

RUN apt-get update \
 && apt-get install -y sudo

RUN python3 -m pip --no-cache-dir install --upgrade pip

RUN python3 -m pip install Sphinx recommonmark sphinx_markdown_tables breathe

# install basic dependencies globally

RUN echo "root:demo" | chpasswd

# create local user for outside access (X and volumes)

ARG UID=1000
RUN adduser demo --gecos "" --disabled-password --uid $UID && \
  chown demo:demo /home/demo && \
  echo "demo:demo" | chpasswd

RUN adduser demo sudo && \
  echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

USER demo


