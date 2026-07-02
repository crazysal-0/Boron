import os, osproc
import args

proc runCapture(cmd: string): (int, string) =
  let res = execCmdEx(cmd)
  (res.exitCode, res.output)

when isMainModule:
  let cfg = parseArgs()

  let asmFile = "out.asm"
  let objFile = "out.o"
  let exeFile = cfg.output

  # --- resolve boronc path safely ---
  let boronc =
    if findExe("boronc") != "":
      "boronc"
    else:
      "../bin/boronc"

  let cmd = boronc & " " & cfg.file

  # --- run compiler ---
  let (code, asmOut) = runCapture(cmd)

  # ALWAYS show output (important for errors)
  echo asmOut

  if code != 0:
    quit(1)

  # --- write asm ---
  writeFile(asmFile, asmOut)

  # --- assemble ---
  if execCmd("nasm -f elf64 " & asmFile & " -o " & objFile) != 0:
    quit("nasm failed")

  # --- link ---
  if execCmd("ld " & objFile & " -o " & exeFile) != 0:
    quit("ld failed")

  echo "built: ", exeFile

  # --- cleanup ---
  if not cfg.showTempFiles:
    discard tryRemoveFile(asmFile)
    discard tryRemoveFile(objFile)