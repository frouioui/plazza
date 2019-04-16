pipeline {
    agent {
        docker {
            image 'epitechcontent/epitest-docker'
        }
    }

    stages {
        stage('Setup') {
            steps {
                sh 'chmod +x ./ci/script/*.sh'
                sh 'mkdir art'
            }
        }

        stage('Build') {
            steps {
                timeout(time: 20) {
                    sh './ci/script/build.sh > ./art/build.txt'
                }
            }
            post {
                always {
                    archiveArtifacts(fingerprint: true, artifacts: 'art/build.txt', allowEmptyArchive: true)
                }
            }
        }

        stage('Tests') {
            steps {
                retry(count: 3) {
                    timeout(time: 20) {
                        sh './ci/script/unit_test.sh > ./art/unit_test.txt'
                    }
                }
            }
            post {
                always {
                archiveArtifacts(artifacts: 'art/unit_test.txt', allowEmptyArchive: true, fingerprint: true)
                }
            }
        }
    }
}