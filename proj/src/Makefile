PROG=proj

.PATH: ${.CURDIR}/controller/keyboard
.PATH: ${.CURDIR}/controller/mouse
.PATH: ${.CURDIR}/controller/timer
.PATH: ${.CURDIR}/controller/video_card/
.PATH: ${.CURDIR}/controller/
.PATH: ${.CURDIR}/model/game/
.PATH: ${.CURDIR}/model/xpm/
.PATH: ${.CURDIR}/model/modes/
.PATH: ${.CURDIR}/view/

SRCS = 	main.c timer.c mouse.c keyboard.c menu.c gpu.c game.c pieces.c board.c player.c viewer.c utils.c sprite.c

CFLAGS += -pedantic 

DPADD += ${LIBLCF}
LDADD += -Wall -llcf -lxpm -llm

.include <minix.lcom.mk>
