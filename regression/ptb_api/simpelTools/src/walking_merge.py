import os
import shutil


def overwrite_merge_Tree(sourceRoot, destRoot):
  #https://stackoverflow.com/questions/22588225/how-do-you-merge-two-directories-or-move-with-replace-from-the-windows-command
  '''
  Updates destenation root, overwrites existing files.
  :param sourceRoot: Root folder from wehere to copy the files
  :param destRoot: Destination folder where new folders and files are created and new files are added
  :return: !=0
  '''
  if not os.path.exists(destRoot):
    return 1
  ok = 0
  for path, dirs, files in os.walk(sourceRoot):
    relPath = os.path.relpath(path, sourceRoot)
    destPath = os.path.join(destRoot, relPath)
    if not os.path.exists(destPath):
      print("create: %s"%destPath)
      os.makedirs(destPath)
    for file in files:
      destFile = os.path.join(destPath, file)
      if os.path.isfile(destFile):
        print "\n...Will overwrite existing file: " + os.path.join(relPath, file)
        #ok = False
        #continue
      srcFile = os.path.join(path, file)
      # print "rename", srcFile, destFile
      # os.rename(srcFile, destFile) # makes move
      print("copy %s to %s"%(srcFile, destFile))
      shutil.copy(srcFile, destFile)
  # clean source
  #for path, dirs, files in os.walk(sourceRoot, False):
  #  if len(files) == 0 and len(dirs) == 0:
  #    print("remove: %s"%path)
  #    os.rmdir(path)
  return ok