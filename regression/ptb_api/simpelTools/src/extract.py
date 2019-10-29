import os,tarfile, sys


# Extract given *.tar.gz to destination directory
# warning this function is temporarely changing the current working directory!
# source: http://code.activestate.com/recipes/442503-extracting-targz-files-in-windows/
#param tarGzFile Tararchive
#param destDir Dir where to extract the tar-file to
def extractTarGz(tarGzFile, destdir):
  dirBackup = os.getcwd()

  err = 0
  try:
    os.chdir(destdir)
    tar = tarfile.open(tarGzFile, 'r:gz')
    for item in tar:
      print "[pirate][unzip]: %s" % (item)
      tar.extract(item)
  except IndexError, e:
    print("Error: %s\n Have you specified a file to untar?" % (e))
    err = 1
  except Exception, e:
    print ("Error: %s" % (e))
    name = os.getcwd()
    print(name[:name.rfind('.')], '<filename>')
    err = 1
  os.chdir(dirBackup)
  return err





print len(sys.argv)

if len(sys.argv)!= 3:
  print("usage: *.py Tar-file /directory/to/extract/to/which/exists")
  exit(-3)

tarArchive = sys.argv[1]
destinationDirectory = sys.argv[2]
print "[pirate][unzip][err]: Job: extract <%s> to <%s>"%(sys.argv[1], sys.argv[2])
# debug
# tarArchive = '/home/aballmert/Downloads/x15.tar.gz'
# destinationDirectory = '/home/aballmert/Downloads/extractPath'
# destination


if False == os.path.isfile(tarArchive):
  print("[pirate][unzip][err]: Archive is not a file <%s>"%tarArchive)
  exit(-5)

elif(False == tarArchive.endswith(".tar.gz")):
  print("[pirate][unzip][err]: Archive does not end with .tar.gz <%s>"%tarArchive)
  exit(-6)

if (False == os.path.isdir(destinationDirectory)):
  print("[pirate][unzip][err]: Destinationdir does not exist: <%s>"%destinationDirectory)
  exit(-4)


exit(extractTarGz(sys.argv[1], sys.argv[2]))
