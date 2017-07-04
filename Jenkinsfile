pipeline {
    agent any

    stages {
        stage('Clean before build') {
            steps {
                sh 'rm -rf .[^.] .??* *'
            }
        }
        stage('Checkout') {
            steps {
                checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], submoduleCfg: [], userRemoteConfigs: [[url: 'https://github.com/muhkuh-sys/org.muhkuh.tools-flasher.git']]])
            }
        }
        stage('Build Artefacts') {
            steps {
                sh './.lxc_build_artefacts.sh'
            }
            post {
                failure {
                    /* Stop and remove the running container. Do not fail on this commands. */
                    sh 'lxc stop c0 || true'
                    sh 'lxc delete c0 || true'
                }
            }
        }
        stage('Save Artifacts') {
            steps {
                archive 'targets/*.xml,targets/*.zip,targets/*.hash,targets/*.pom'
            }
        }
        stage('Clean after build') {
            steps {
                sh 'rm -rf .[^.] .??* *'
            }
        }
    }
}
