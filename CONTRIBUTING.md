meta-java contribution guidelines
=================================

Contributing via GitLab.com
---------------------------

To contribute to this layer you may fork the repository and create a merge
request at https://gitlab.com/meta-java/meta-java.

Please refer to: https://docs.gitlab.com/ee/user/project/merge_requests/
for more information on merge requests in GitLab.

Contributing via E-Mail
-----------------------

To contribute to this layer you may submit the patches for review to the
mailing list (openembedded-devel@lists.openembedded.org).

Please refer to:
https://wiki.yoctoproject.org/wiki/Contribution_Guidelines#General_Information

for some useful guidelines to be followed when submitting patches.

Mailing list:

    http://lists.yoctoproject.org/mailman/listinfo/yocto-patches

Source code:

    git://git.yoctoproject.org/meta-java
    http://git.yoctoproject.org/git/meta-java

When creating single patches, please use something like:

    git format-patch -M -s --subject-prefix='meta-java][PATCH' -1

When creating a patch series, please add a cover letter describing it shortly.
Therefore use something like:

    git format-patch -M -s --cover-letter --subject-prefix='meta-java][PATCH' origin

When sending patches, please use something like:

    git send-email --to yocto-patches@lists.yoctoproject.org <generated patch(es)>

Please add the main layer maintainers to CC:

  Henning Heinold <henning@itconsulting-heinold.de>
  Otavio Salvador <otavio@ossystems.com.br>
  Richard Leitner <richard.leitner@skidata.com>
