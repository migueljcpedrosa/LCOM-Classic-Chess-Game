PROG=proj

.PATH: ${.CURDIR}/controller/
.PATH: ${.CURDIR}/controller/video_card/
.PATH: ${.CURDIR}/model/game/
.PATH: ${.CURDIR}/model/xpm/

SRCS = 	main.c 

CFLAGS += -pedantic -DLAB3

DPADD += ${LIBLCF}
LDADD += -Wall -llcf -lxpm -llm

.include <minix.lcom.mk>
