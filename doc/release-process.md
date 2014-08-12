Release Process
====================


###update (commit) version in sources

	contrib/verifysfbinaries/verify.sh
	doc/README*
	share/setup.nsi
	src/clientversion.h (change CLIENT_VERSION_IS_RELEASE to true)
	./configure.ac (change (_CLIENT_VERSION_IS_RELEASE, true))

###tag version in git

	git tag -s v(new version, e.g. 0.8.0)

###write release notes. git shortlog helps a lot, for example:

	git shortlog --no-merges v(current version, e.g. 0.7.2)..v(new version, e.g. 0.8.0)
	or alternatively
	git log --date=short --pretty=format:"%h - %an, %ad : %s  " v(current version, e.g. 1.4.1)..v(new version, e.g. 2.0.0) > git.log


* * *

###update gitian

 In order to take advantage of the new caching features in gitian, be sure to update to a recent version (e9741525c or higher is recommended)

###perform gitian builds

 From a directory containing the reddcoin source, gitian-builder and gitian.sigs
  
	export SIGNER=(your gitian key, ie bluematt, sipa, etc)
	export VERSION=(new version, e.g. 0.8.0)
	pushd ./reddcoin
	git checkout v${VERSION}
	popd
	pushd ./gitian-builder

###fetch and build inputs: (first time, or when dependency versions change)
 
	mkdir -p inputs; cd inputs/

 Register and download the Apple SDK: (see OSX Readme for details)
 
 https://developer.apple.com/downloads/download.action?path=Developer_Tools/xcode_4.6.3/xcode4630916281a.dmg
 
 Using a Mac, create a tarball for the 10.7 SDK and copy it to the inputs directory:
 
	tar -C /Volumes/Xcode/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/ -czf MacOSX10.7.sdk.tar.gz MacOSX10.7.sdk

 Build Reddcoin Core for Linux, Windows, and OS X:
  
	./bin/gbuild --commit reddcoin=v${VERSION} ../reddcoin/contrib/gitian-descriptors/gitian-linux.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-linux --destination ../gitian.sigs/ ../reddcoin/contrib/gitian-descriptors/gitian-linux.yml
	pushd build/out
	zip -r reddcoin-${VERSION}-linux-gitian.zip *
	mv reddcoin-${VERSION}-linux-gitian.zip ../../../
	popd
	./bin/gbuild --commit reddcoin=v${VERSION} ../reddcoin/contrib/gitian-descriptors/gitian-win.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win --destination ../gitian.sigs/ ../reddcoin/contrib/gitian-descriptors/gitian-win.yml
	pushd build/out
	zip -r reddcoin-${VERSION}-win-gitian.zip *
	mv reddcoin-${VERSION}-win-gitian.zip ../../../
	popd
        ./bin/gbuild --commit reddcoin=v${VERSION} ../reddcoin/contrib/gitian-descriptors/gitian-osx.yml
        ./bin/gsign --signer $SIGNER --release ${VERSION}-osx --destination ../gitian.sigs/ ../reddcoin/contrib/gitian-descriptors/gitian-osx.yml
	pushd build/out
	mv Reddcoin-Qt.dmg ../../../
	popd
	popd

  Build output expected:

  1. linux 32-bit and 64-bit binaries + source (reddcoin-${VERSION}-linux-gitian.zip)
  2. windows 32-bit and 64-bit binaries + installer + source (reddcoin-${VERSION}-win-gitian.zip)
  3. OSX installer (Reddcoin-Qt.dmg)
  4. Gitian signatures (in gitian.sigs/${VERSION}-<linux|win|osx>/(your gitian key)/

repackage gitian builds for release as stand-alone zip/tar/installer exe

**Linux .tar.gz:**

	unzip reddcoin-${VERSION}-linux-gitian.zip -d reddcoin-${VERSION}-linux
	tar czvf reddcoin-${VERSION}-linux.tar.gz reddcoin-${VERSION}-linux
	rm -rf reddcoin-${VERSION}-linux

**Windows .zip and setup.exe:**

	unzip reddcoin-${VERSION}-win-gitian.zip -d reddcoin-${VERSION}-win
	mv reddcoin-${VERSION}-win/reddcoin-*-setup.exe .
	zip -r reddcoin-${VERSION}-win.zip reddcoin-${VERSION}-win
	rm -rf reddcoin-${VERSION}-win

**Mac OS X .dmg:**

	mv Reddcoin-Qt.dmg reddcoin-${VERSION}-osx.dmg

###Next steps:

Commit your signature to gitian.sigs:

	pushd gitian.sigs
	git add ${VERSION}-linux/${SIGNER}
	git add ${VERSION}-win/${SIGNER}
	git add ${VERSION}-osx/${SIGNER}
	git commit -a
	git push  # Assuming you can push to the gitian.sigs tree
	popd

-------------------------------------------------------------------------

### After 3 or more people have gitian-built and their results match:

- Perform code-signing.

    - Code-sign Windows -setup.exe (in a Windows virtual machine using signtool)

    - Code-sign MacOSX .dmg

  Note: only John has the code-signing keys currently.

- Create `SHA256SUMS.asc` for the builds, and GPG-sign it:
```bash
sha256sum * > SHA256SUMS
gpg --digest-algo sha256 --clearsign SHA256SUMS # outputs SHA256SUMS.asc
rm SHA256SUMS
```
(the digest algorithm is forced to sha256 to avoid confusion of the `Hash:` header that GPG adds with the SHA256 used for the files)

- Upload zips and installers, as well as `SHA256SUMS.asc` from last step, to github release

- Update reddcoin.com version
- Upload gitian zips to github releases

- Announce the release:

  - Release sticky on reddcointalk: https://www.reddcointalk.org/category/1/announcements

  - Reddheads mailing list

  - Update title of #reddcoin on Freenode IRC

  - Reddit /r/Reddcoin,

- Add release notes for the new version to the directory `doc/release-notes` in git master

- Celebrate 
