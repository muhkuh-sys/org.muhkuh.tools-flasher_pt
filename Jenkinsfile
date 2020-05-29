import groovy.json.JsonSlurperClassic

node {
    def ARTIFACTS_PATH1 = 'targets/jonchki/flasher_cli'
    def ARTIFACTS_PATH2 = 'targets/jonchki/repository/org/muhkuh/tools/flasher_pt/*'
    def strBuilds = env.JENKINS_SELECT_BUILDS
    def atBuilds = new JsonSlurperClassic().parseText(strBuilds)

    docker.image("mbs_ubuntu_1804_x86_64").inside('-u root') {
        /* Clean before the build. */
        sh 'rm -rf .[^.] .??* *'

        checkout([$class: 'GitSCM',
            branches: [[name: '*/master']],
            doGenerateSubmoduleConfigurations: false,
            extensions: [
                [$class: 'SubmoduleOption',
                    disableSubmodules: false,
                    recursiveSubmodules: true,
                    reference: '',
                    trackingSubmodules: false
                ]
            ],
            submoduleCfg: [],
            userRemoteConfigs: [[url: 'https://github.com/muhkuh-sys/org.muhkuh.tools-flasher_pt.git']]
        ])

        /* Build the flasher. */
        stage("flasher"){
            sh "python3 mbs/mbs"
        }

        atBuilds.each { atEntry ->
            stage("${atEntry[0]} ${atEntry[1]} ${atEntry[2]}"){
                /* Build the project. */
                sh "python3 build_artifact.py ${atEntry[0]} ${atEntry[1]} ${atEntry[2]}"
            }
        }

        /* Archive all artifacts. */
        archiveArtifacts artifacts: "${ARTIFACTS_PATH1}/*.tar.gz,${ARTIFACTS_PATH1}/*.zip,${ARTIFACTS_PATH2}/*.hash,${ARTIFACTS_PATH2}/*.pom,${ARTIFACTS_PATH2}/*.xml,${ARTIFACTS_PATH2}/*.zip"

        /* Clean up after the build. */
        sh 'rm -rf .[^.] .??* *'
    }
}
