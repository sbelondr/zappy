PATH_GODOT = "$(HOME)/Godot_v3.4.2"
PLATEFORME_GODOT = "Linux/X11"
PROJECT_GODOT = "graphique/project.godot"

all: server graphique

server:
	echo coucu
	make -C server

graphique:
	$(PATH_GODOT) --export  "$(PLATEFORME_GODOT)" $(PROJECT_GODOT)

.PHONY : all server graphique
