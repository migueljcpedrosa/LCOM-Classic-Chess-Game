PROG=proj

.PATH: ${.CURDIR}/drivers/keyboard
.PATH: ${.CURDIR}/drivers/mouse
.PATH: ${.CURDIR}/drivers/timer
.PATH: ${.CURDIR}/drivers/video_card/
.PATH: ${.CURDIR}/drivers/
.PATH: ${.CURDIR}/model/game/
.PATH: ${.CURDIR}/model/xpm/
.PATH: ${.CURDIR}/model/modes/
.PATH: ${.CURDIR}/model/cursor/
.PATH: ${.CURDIR}/view/

SRCS = 	main.c timer.c mouse.c keyboard.c menu.c gpu.c game.c pieces.c board.c player.c viewer.c utils.c sprite.c cursor.c

CFLAGS += -pedantic

DPADD += ${LIBLCF}
LDADD += -Wall -llcf -lxpm -llm

.include <minix.lcom.mk>
