import os
from language_tool_python import LanguageTool

DOCS_PATH = "docs"  # change if your reST files are elsewhere
tool = LanguageTool('en-US')

omit_list = ["utilize", "leverage"]  # grow this list

def scan_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
        matches = tool.check(content)

        for match in matches:
            if "FUTURE_TENSE" in match.ruleId or "will" in match.message.lower():
                print(f"[Future Tense] {file_path}:{match.line}:{match.message}")

            if "PASSIVE_VOICE" in match.ruleId:
                print(f"[Passive Voice?] {file_path}:{match.line}:{match.message}")

            if match.ruleId not in ["FUTURE_TENSE", "PASSIVE_VOICE"]:
                print(f"[Grammar] {file_path}:{match.line}:{match.message}")

        for word in omit_list:
            if word in content:
                print(f"[Omit Word] Found '{word}' in {file_path}")

def scan_dir(root):
    for dirpath, _, filenames in os.walk(root):
        for filename in filenames:
            if filename.endswith(".rst"):
                scan_file(os.path.join(dirpath, filename))

if __name__ == "__main__":
    scan_dir(DOCS_PATH)
