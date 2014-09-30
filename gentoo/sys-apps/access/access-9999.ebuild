EAPI=5

inherit git-2

DESCRIPTION="Wrapper around the access() syscall"
HOMEPAGE="https://github.com/atalax/access"
EGIT_REPO_URI="https://github.com/atalax/access.git"

LICENSE="MIT"
SLOT="0"
KEYWORDS="x86 amd64 arm"
IUSE=""

DEPEND=""
RDEPEND="${DEPEND}"

src_compile() {
	emake
}

src_install() {
	dobin access
}
