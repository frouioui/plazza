pipeline {
  agent none

  triggers {
    cron('H * * * *')
  }

  options {
    timestamps()
    timeout(10)
  }

  stages {

    stage('Build') {
      agent {
        docker {
          image 'epitechcontent/epitest-docker'
        }
      }
      steps {
        timeout(time: 60) {
          sh 'make fclean'
          sh 'make'
          sh 'make clean'
          sh 'make re && make fclean'
          sh 'make plazza && make fclean'
          sh 'make all && make fclean'
        }
      }
    }

    stage('Tests') {
      agent {
        docker {
          image 'epitechcontent/epitest-docker'
        }
      }
      steps {
        sh 'mkdir coverage_build'
        retry(count: 3) {
          timeout(time: 60) {
            sh 'make tests_run'
          }
        }
        sh 'gcovr -x > coverage_build/coverage.xml'
        cobertura coberturaReportFile: 'coverage_build/coverage.xml', conditionalCoverageTargets: '70, 0, 0', failNoReports: false, failUnhealthy: false, failUnstable: false, lineCoverageTargets: '80, 0, 0', maxNumberOfBuilds: 10, methodCoverageTargets: '80, 0, 0', onlyStable: false, sourceEncoding: 'ASCII'
        junit 'report/*.xml'
      }
    }

    stage('Deploy') {
      agent any
      when {
        anyOf {
          branch 'master'
          branch 'dev'
        }
        allOf {
          not {
            changeRequest()
          }
          not {
            triggeredBy('TimerTrigger')
          }
        }
      }
      steps {
        sshagent (credentials: ['epitech-global']) {
          sh "git push git@git.epitech.eu:/florent.poinsard@epitech.eu/CCP_plazza_2018 --force ${env.BRANCH_NAME}:${env.BRANCH_NAME}"
        }
      }
    }
  }
}