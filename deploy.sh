pwd
TARGET_FOLDER=$(cat target_folder.txt)
PACKAGE_FILE_NAME="${TARGET_FOLDER}-0.0.${TRAVIS_BUILD_NUMBER}-Linux.deb"
curl -T build/${PACKAGE_FILE_NAME} -upokachopotun:$BINTRAY_API_KEY "https://api.bintray.com/content/pokachopotun-organization/otus-cpp/${TARGET_FOLDER}/$TRAVIS_BUILD_NUMBER/${PACKAGE_FILE_NAME};deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1"
