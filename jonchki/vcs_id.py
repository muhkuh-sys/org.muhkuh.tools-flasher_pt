from dulwich import porcelain
import re


def get(strRepositoryPath):
    # The default version is 'unknown'.
    strProjectVersionVcs = 'unknown'
    strProjectVersionVcsLong = 'unknown'

    try:
        strGitId = porcelain.describe(
            strRepositoryPath,
            abbrev=12,
            long=True,
            dirty='+'
        )
        tMatch = re.match(r'[0-9a-f]{12}\+?$', strGitId)
        if tMatch is not None:
            # This is a repository with no tags.
            # Use the raw SHA sum.
            strProjectVersionVcs = strGitId
            strProjectVersionVcsLong = strGitId
        else:
            tMatch = re.match(
                r'v(\d+(\.\d+)*)-(\d+)-g([0-9a-f]{12})$',
                strGitId
            )
            if tMatch is not None:
                ulRevsSinceTag = int(tMatch.group(3))
                if ulRevsSinceTag == 0:
                    # This is a repository which is exactly on a
                    # tag. Use the tag name.
                    strProjectVersionVcs = tMatch.group(1)
                    strProjectVersionVcsLong = '%s-%s' % (
                        tMatch.group(1),
                        tMatch.group(4)
                    )
                else:
                    # This is a repository with commits after
                    # the last tag. Use the checkin ID.
                    strProjectVersionVcs = tMatch.group(4)
                    strProjectVersionVcsLong = tMatch.group(4)
            else:
                tMatch = re.match(
                    r'v(\d+(\.\d+)*)-(\d+)-g([0-9a-f]{12})\+?$',
                    strGitId
                )
                if tMatch is not None:
                    ulRevsSinceTag = int(tMatch.group(3))
                    if ulRevsSinceTag == 0:
                        # This is a repository on a tag, but it has
                        # modified files. Use the tag name and the '+'.
                        strProjectVersionVcs = '%s+' % (tMatch.group(1))
                        strProjectVersionVcsLong = '%s-%s+' % (
                            tMatch.group(1),
                            tMatch.group(4)
                        )
                    else:
                        # This is a repository with commits after the last tag
                        # and modified files. Use the checkin ID and the '+'.
                        strProjectVersionVcs = '%s+' % (tMatch.group(4))
                        strProjectVersionVcsLong = '%s+' % (tMatch.group(4))
                else:
                    # The description has an unknown format.
                    strProjectVersionVcs = strGitId
                    strProjectVersionVcsLong = strGitId

        strProjectVersionVcs = 'GIT%s' % strProjectVersionVcs
        strProjectVersionVcsLong = 'GIT%s' % strProjectVersionVcsLong
    except Exception as e:
        pass

    return strProjectVersionVcs, strProjectVersionVcsLong
