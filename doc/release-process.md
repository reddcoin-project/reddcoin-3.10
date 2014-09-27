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

 Download remaining inputs, and build everything:
 
	wget 'http://miniupnp.free.fr/files/download.php?file=miniupnpc-1.9.20140701.tar.gz' -O miniupnpc-1.9.20140701.tar.gz
	wget 'https://www.openssl.org/source/openssl-1.0.1h.tar.gz'
	wget 'http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz'
	wget 'http://zlib.net/zlib-1.2.8.tar.gz'
	wget 'ftp://ftp.simplesystems.org/pub/png/src/history/libpng16/libpng-1.6.8.tar.gz'
	wget 'https://fukuchi.org/works/qrencode/qrencode-3.4.3.tar.bz2'
	wget 'https://downloads.sourceforge.net/project/boost/boost/1.55.0/boost_1_55_0.tar.bz2'
	wget 'https://svn.boost.org/trac/boost/raw-attachment/ticket/7262/boost-mingw.patch' -O boost-mingw-gas-cross-compile-2013-03-03.patch
	wget 'https://download.qt-project.org/official_releases/qt/5.2/5.2.0/single/qt-everywhere-opensource-src-5.2.0.tar.gz'
	wget 'https://download.qt-project.org/official_releases/qt/5.2/5.2.1/single/qt-everywhere-opensource-src-5.2.1.tar.gz'
	wget 'https://download.qt-project.org/archive/qt/4.6/qt-everywhere-opensource-src-4.6.4.tar.gz'
	wget 'https://protobuf.googlecode.com/files/protobuf-2.5.0.tar.bz2'
	wget 'https://github.com/mingwandroid/toolchain4/archive/10cc648683617cca8bcbeae507888099b41b530c.tar.gz'
	wget 'http://www.opensource.apple.com/tarballs/cctools/cctools-809.tar.gz'
	wget 'http://www.opensource.apple.com/tarballs/dyld/dyld-195.5.tar.gz'
	wget 'http://www.opensource.apple.com/tarballs/ld64/ld64-127.2.tar.gz'
	wget 'http://pkgs.fedoraproject.org/repo/pkgs/cdrkit/cdrkit-1.1.11.tar.gz/efe08e2f3ca478486037b053acd512e9/cdrkit-1.1.11.tar.gz'
	wget 'https://github.com/theuni/libdmg-hfsplus/archive/libdmg-hfsplus-v0.1.tar.gz'
	wget 'http://llvm.org/releases/3.2/clang+llvm-3.2-x86-linux-ubuntu-12.04.tar.gz' -O clang-llvm-3.2-x86-linux-ubuntu-12.04.tar.gz
	wget 'https://raw.githubusercontent.com/theuni/osx-cross-depends/master/patches/cdrtools/genisoimage.diff' -O cdrkit-deterministic.patch
	cd ..
	./bin/gbuild ../reddcoin/contrib/gitian-descriptors/boost-linux.yml
	mv build/out/boost-*.zip inputs/
	./bin/gbuild ../reddcoin/contrib/gitian-descriptors/deps-linux.yml
	mv build/out/reddcoin-deps-*.zip inputs/
	./bin/gbuild ../reddcoin/contrib/gitian-descriptors/qt-linux.yml
	mv build/out/qt-*.tar.gz inputs/
	./bin/gbuild ../reddcoin/contrib/gitian-descriptors/boost-win.yml
	mv build/out/boost-*.zip inputs/
	./bin/gbuild ../reddcoin/contrib/gitian-descriptors/deps-win.yml
	mv build/out/reddcoin-deps-*.zip inputs/
	./bin/gbuild ../reddcoin/contrib/gitian-descriptors/qt-win.yml
	mv build/out/qt-*.zip inputs/
	./bin/gbuild ../reddcoin/contrib/gitian-descriptors/protobuf-win.yml
	mv build/out/protobuf-*.zip inputs/
	./bin/gbuild ../reddcoin/contrib/gitian-descriptors/gitian-osx-native.yml
	mv build/out/osx-*.tar.gz inputs/
	./bin/gbuild ../reddcoin/contrib/gitian-descriptors/gitian-osx-depends.yml
	mv build/out/osx-*.tar.gz inputs/
	./bin/gbuild ../reddcoin/contrib/gitian-descriptors/gitian-osx-qt.yml
	mv build/out/osx-*.tar.gz inputs/

 The expected SHA256 hashes of the intermediate inputs are:

    f29b7d9577417333fb56e023c2977f5726a7c297f320b175a4108cf7cd4c2d29  boost-linux32-1.55.0-gitian-r1.zip
    88232451c4104f7eb16e469ac6474fd1231bd485687253f7b2bdf46c0781d535  boost-linux64-1.55.0-gitian-r1.zip
    71e03e434af269dcbf3cb685cd1a5d51b8d2c904b67035eb4e5c1a2623b9f0df  reddcoin-deps-linux32-gitian-r9.zip
    f03be39fb26670243d3a659e64d18e19d03dec5c11e9912011107768390b5268  reddcoin-deps-linux64-gitian-r9.zip
    57e57dbdadc818cd270e7e00500a5e1085b3bcbdef69a885f0fb7573a8d987e1  qt-linux32-4.6.4-gitian-r1.tar.gz
    60eb4b9c5779580b7d66529efa5b2836ba1a70edde2a0f3f696d647906a826be  qt-linux64-4.6.4-gitian-r1.tar.gz
    60dc2d3b61e9c7d5dbe2f90d5955772ad748a47918ff2d8b74e8db9b1b91c909  boost-win32-1.55.0-gitian-r6.zip
    f65fcaf346bc7b73bc8db3a8614f4f6bee2f61fcbe495e9881133a7c2612a167  boost-win64-1.55.0-gitian-r6.zip
    2af17b1968bd7d46b260c8d16474e1f339cde1b9e96265c80f6626ea0c2785a9  reddcoin-deps-win32-gitian-r16.zip
    7608bdf7848101d48ba8a296cb9c29ac68193405f11d8075fb46154ff3476233  reddcoin-deps-win64-gitian-r16.zip
    963e3e5e85879010a91143c90a711a5d1d5aba992e38672cdf7b54e42c56b2f1  qt-win32-5.2.0-gitian-r3.zip
    751c579830d173ef3e6f194e83d18b92ebef6df03289db13ab77a52b6bc86ef0  qt-win64-5.2.0-gitian-r3.zip
    e2e403e1a08869c7eed4d4293bce13d51ec6a63592918b90ae215a0eceb44cb4  protobuf-win32-2.5.0-gitian-r4.zip
    a0999037e8b0ef9ade13efd88fee261ba401f5ca910068b7e0cd3262ba667db0  protobuf-win64-2.5.0-gitian-r4.zip
    512bc0622c883e2e0f4cbc3fedfd8c2402d06c004ce6fb32303cc2a6f405b6df  osx-native-depends-r3.tar.gz
    927e4b222be6d590b4bc2fc185872a5d0ca5c322adb983764d3ed84be6bdbc81  osx-depends-r4.tar.gz
    ec95abef1df2b096a970359787c01d8c45e2a4475b7ae34e12c022634fbdba8a  osx-depends-qt-5.2.1-r4.tar.gz


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
        ./bin/gbuild --commit reddcoin=v${VERSION} ../reddcoin/contrib/gitian-descriptors/gitian-osx-reddcoin.yml
        ./bin/gsign --signer $SIGNER --release ${VERSION}-osx --destination ../gitian.sigs/ ../reddcoin/contrib/gitian-descriptors/gitian-osx-reddcoin.yml
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
gpg --clearsign SHA256SUMS # outputs SHA256SUMS.asc
rm SHA256SUMS
```

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
