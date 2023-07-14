import argparse
from platform_detect import PlatformDetect


def parse():
    tPlatform = PlatformDetect()
    tPlatform.detect()

    tParser = argparse.ArgumentParser(description='Build the artifact.')
    tParser.add_argument(
        'astrJonchkiIDs',
        metavar='JONCHKI_IDS',
        type=str,
        nargs='*',
        help=(
            'Either 0, 2 or 3 argument. 0 arguments build for the current ' +
            'host. 2 arguments are the distribution ID and CPU architecture ' +
            'for targets without a distribution version (like windows). 3 ' +
            'arguments are the distribution ID, distribution version and ' +
            'CPU architecture.'
        )
    )
    tParser.add_argument(
        '--cmake-define',
        dest='astrCMakeDefines',
        metavar='CMAKE_DEFINES',
        type=str,
        nargs='*',
        help='Additional CMake defines.')
    tArgs = tParser.parse_args()

    sizJonchkiIDs = len(tArgs.astrJonchkiIDs)
    if sizJonchkiIDs == 0:
        # No platform was specified on the command line.
        strJonchkiDistributionID = tPlatform.strHostDistributionId
        strJonchkiDistributionVersion = tPlatform.strHostDistributionVersion
        strJonchkiCPUArchitecture = tPlatform.strHostCpuArchitecture

        if strJonchkiDistributionVersion is None:
            strJonchkiPlatformID = '%s_%s' % (
                strJonchkiDistributionID,
                strJonchkiCPUArchitecture
            )
        else:
            strJonchkiPlatformID = '%s_%s_%s' % (
                strJonchkiDistributionID,
                strJonchkiDistributionVersion,
                strJonchkiCPUArchitecture
            )

    elif sizJonchkiIDs == 2:
        # This looks like a windows build.
        strJonchkiDistributionID = tArgs.astrJonchkiIDs[0]
        strJonchkiDistributionVersion = None
        strJonchkiCPUArchitecture = tArgs.astrJonchkiIDs[1]
        if strJonchkiDistributionID != 'windows':
            raise Exception('No distribution version specified. '
                            'This is only possible for windows.')

        strJonchkiPlatformID = '%s_%s' % (
            strJonchkiDistributionID,
            strJonchkiCPUArchitecture
        )

    elif sizJonchkiIDs == 3:
        # This looks like a distribution ID, a distribution version and a CPU
        # architecture.
        strJonchkiDistributionID = tArgs.astrJonchkiIDs[0]
        strJonchkiDistributionVersion = tArgs.astrJonchkiIDs[1]
        strJonchkiCPUArchitecture = tArgs.astrJonchkiIDs[2]

        strJonchkiPlatformID = '%s_%s_%s' % (
            strJonchkiDistributionID,
            strJonchkiDistributionVersion,
            strJonchkiCPUArchitecture
        )

    else:
        raise Exception('Invalid numer of arguments.')

    # Prepare all CMake defines as proper command line options.
    astrCMakeDefines = []
    if tArgs.astrCMakeDefines is not None:
        for strDefine in tArgs.astrCMakeDefines:
            astrCMakeDefines.append('-D' + strDefine)

    tPlatform = dict(
        distribution_id=strJonchkiDistributionID,
        distribution_version=strJonchkiDistributionVersion,
        cpu_architecture=strJonchkiCPUArchitecture,
        platform_id=strJonchkiPlatformID,
        host_cpu_architecture=tPlatform.strHostCpuArchitecture,
        host_distribution_id=tPlatform.strHostDistributionId,
        host_distribution_version=tPlatform.strHostDistributionVersion,
        host_standard_archive_format=tPlatform.strStandardArchiveFormat,
        cmake_defines=astrCMakeDefines
    )

    return tPlatform


def to_jonchki_args(tPlatform):
    # Create the command line options for the selected platform.
    astrJonchkiPlatform = []
    if tPlatform['distribution_id'] is not None:
        astrJonchkiPlatform.extend([
            '--distribution-id', tPlatform['distribution_id']
        ])
        if tPlatform['distribution_version'] is None:
            astrJonchkiPlatform.append('--empty-distribution-version')
        else:
            astrJonchkiPlatform.extend([
                '--distribution-version', tPlatform['distribution_version']
            ])
        astrJonchkiPlatform.extend([
            '--cpu-architecture', tPlatform['cpu_architecture']
        ])

    return astrJonchkiPlatform
