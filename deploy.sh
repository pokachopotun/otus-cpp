BUILD_FOLDER=$(cat build_folder.txt)
PACKAGE_FILE_NAME="${BUILD_FOLDER}-0.0.${TRAVIS_BUILD_NUMBER}-Linux.deb"
curl -T ${PACKAGE_FILE_NAME} -upokachopotun:$BINTRAY_API_KEY "https://api.bintray.com/content/pokachopotun/otus-cpp/${BUILD_FOLDER}/$TRAVIS_BUILD_NUMBER/${PACKAGE_FILE_NAME};deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1"
