import os

from simpelTools.src.logging_default import *


def generate_randome_file_by_size_and_name(path_generated_file, test_binary_size):
    """
    simply generates a binary file from given length and given size.
    Removes a old file with the same name!
    :param path_generated_file:
    :param test_binary_size:
    :return:
    """
    try:
        os.remove(path_generated_file)
    except BaseException as e:
        pass
        # l.info(e)

    if test_binary_size > 1024*1024*200:
        raise MemoryError('Cowardly refusing to generate a file with more than 200MB of random test data.'
                          'Might not be necessary and a programmers error.')

    with open(path_generated_file, 'wb') as fout:
        try:
            fout.write(os.urandom(test_binary_size))
            l.info("Generated binary file size 0x%x/0d%d to: %s" % (test_binary_size,test_binary_size, path_generated_file))
        except MemoryError as e:
            l.error("Error raised, probably because of a too large write attempt of %d bytes at once." % test_binary_size)
            raise e


def create_a_folder_if_not_existing(folder, additional_error_message=""):
    """
    Create a folder on given location, if it does not exist.
    The path of the rootfolder has to exist!
    :param folder: full path of folder which will be created
    :param message: optional parameter for additional info in case of error
    :return:
    """
    try:
        os.mkdir(folder)
    except OSError as e:
        l.debug('Skip logfile folder creation, folder exists', folder)


#        if e.args == (17, 'File exists'):
#            l.debug('Skip logfile folder creation, folder exists', folder)
#        else:
#            l.error("Can't create folder >%s<. Reason %s" % (folder, e.strerror))
#            raise e


def delete_all_files_in_folder(folder_with_files_to_be_deleted):
    try:
        files_to_be_deleted = os.listdir(folder_with_files_to_be_deleted)
    except BaseException as e:
        l.error("folder to reset empty?! %s" % e)
    else:
        if files_to_be_deleted:
            for file_to_be_deleted in files_to_be_deleted:
                l.debug("remove old file: %s" % file_to_be_deleted)
                try:
                    os.remove(os.path.join(folder_with_files_to_be_deleted, file_to_be_deleted))
                except BaseException as e:
                    l.info(e)
