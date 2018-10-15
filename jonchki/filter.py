import string


def file(strInput, strOutput, atMapping):
    # Read the input file. Read it as binary to preserve the newlines.
    tFile = open(strInput, 'rb')
    strTemplate = tFile.read()
    tFile.close()

    # Substitute all keywords in the template.
    tTemplate = string.Template(strTemplate)
    strText = tTemplate.substitute(atMapping)

    # Write the result to the output file.
    tFile = open(strOutput, 'wb')
    tFile.write(strText)
    tFile.close()
