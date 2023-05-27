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
.PATH: ${.CURDIR}/model/menu/
.PATH: ${.CURDIR}/model/name/
.PATH: ${.CURDIR}/view/
.PATH: ${.CURDIR}/controller/
.PATH: ${.CURDIR}/state/

SRCS = 	main.c timer.c mouse.c keyboard.c menu.c gpu.c game.c pieces.c board.c player.c viewer.c utils.c sprite.c cursor.c menu_viewer.c name_viewer.c menu_controller.c name_controller.c state.c name_input.c

CFLAGS += -pedantic

DPADD += ${LIBLCF}
LDADD += -Wall -llcf -lxpm -llm

.include <minix.lcom.mk>
