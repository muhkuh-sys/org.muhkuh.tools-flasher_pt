import sys
from platform_detect import PlatformDetect


def parse():
    tPlatform = PlatformDetect()
    tPlatform.detect()

    argc = len(sys.argv)
    if argc == 1:
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

    elif argc == 3:
        # The command line has 2 arguments.
        # This looks like a windows build.
        strJonchkiDistributionID = sys.argv[1]
        strJonchkiDistributionVersion = None
        strJonchkiCPUArchitecture = sys.argv[2]
        if strJonchkiDistributionID != 'windows':
            raise Exception('No distribution version specified. '
                            'This is only possible for windows.')

        strJonchkiPlatformID = '%s_%s' % (
            strJonchkiDistributionID,
            strJonchkiCPUArchitecture
        )

    elif argc == 4:
        # The command has 3 arguments.
        # This looks like a distribution ID, a distribution version and a CPU
        # architecture.
        strJonchkiDistributionID = sys.argv[1]
        strJonchkiDistributionVersion = sys.argv[2]
        strJonchkiCPUArchitecture = sys.argv[3]

        strJonchkiPlatformID = '%s_%s_%s' % (
            strJonchkiDistributionID,
            strJonchkiDistributionVersion,
            strJonchkiCPUArchitecture
        )

    else:
        raise Exception('Invalid numer of arguments.')

    tPlatform = dict(
        distribution_id=strJonchkiDistributionID,
        distribution_version=strJonchkiDistributionVersion,
        cpu_architecture=strJonchkiCPUArchitecture,
        platform_id=strJonchkiPlatformID,
        host_cpu_architecture=tPlatform.strHostCpuArchitecture,
        host_distribution_id=tPlatform.strHostDistributionId,
        host_distribution_version=tPlatform.strHostDistributionVersion,
        host_standard_archive_format=tPlatform.strStandardArchiveFormat
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
