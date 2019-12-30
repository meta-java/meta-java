# HowTo Update OpenJDK 8 #

1. Determine latest ga version:
     curl -s "https://hg.openjdk.java.net/jdk8u/jdk8u/tags" | grep -m 1 "jdk8u.*ga" | sed 's/-ga$//g'
2. Rename OpenJDK/OpenJRE bb files to the matching release version
3. Adapt the CHANGESET_ID for aarch32 based on:
     curl -s https://hg.openjdk.java.net/aarch32-port/jdk8u/tags | grep "jdk8u.*ga-aarch32-"
4. Adapt the CHANGESET_ID for aarch64 based on:
     curl -s https://hg.openjdk.java.net/aarch64-port/jdk8u-shenandoah/tags | grep "aarch64-shenandoah-jdk8u.*-"
5. Adapt source archive checksums by executing the script
     ./docs/update8checksums.sh
6. Check if any patch got upstreamed (and remove if so)
7. Re-apply all other patches and format them again
    for git: git format-patch --src-prefix=a/y/ --dst-prefix=b/y/ -n --start-number=x jdk8uXXX-ga
8. Test for x86_64, aarch32 & aarch64 (at least using testimage in qemu)
9. Send a patch ;-)
