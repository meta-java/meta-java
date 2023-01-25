# meta-java contribution guidelines

## Contributing via GitHub.com

To contribute to this layer you may fork the repository and create a pull
request at https://github.com/meta-java/meta-java.

## Contributing via E-Mail

To contribute to this layer you may submit the patches for review to the
mailing list (openembedded-devel@lists.openembedded.org).

Please refer to:
https://wiki.yoctoproject.org/wiki/Contribution_Guidelines#General_Information

for some useful guidelines to be followed when submitting patches.

Mailing list:

    http://lists.openembedded.org/mailman/listinfo/openembedded-devel

Source code:

    git://git.yoctoproject.org/meta-java
    http://git.yoctoproject.org/git/meta-java

When creating single patches, please use something like:

    git format-patch -M -s --subject-prefix='meta-java][PATCH' -1

When creating a patch series, please add a cover letter describing it shortly.
Therefore use something like:

    git format-patch -M -s --cover-letter --subject-prefix='meta-java][PATCH' origin

When sending patches, please use something like:

    git send-email --to openembedded-devel@lists.openembedded.org <generated patch(es)>

Please add the main layer maintainers to CC:

  Henning Heinold <henning@itconsulting-heinold.de>
  Otavio Salvador <otavio@ossystems.com.br>
  Richard Leitner <dev@g0hl1n.net>
