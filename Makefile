GODOT = "Godot"
PLATEFORME_GODOT = "Linux/X11"
PROJECT_GODOT = "graphique/project.godot"
BUILD_DIR = "build/"
PATH_GODOT = "$(BUILD_DIR)$(GODOT)"

all: server graphique

server:
	make -C server

$(PATH_GODOT):
	mkdir -p $(BUILD_DIR)
	curl https://downloads.tuxfamily.org/godotengine/3.4.4/Godot_v3.4.4-stable_x11.64.zip > $(BUILD_DIR)godot.zip
	unzip $(BUILD_DIR)godot.zip -d $(BUILD_DIR)unzipped
	mv $(BUILD_DIR)/unzipped/* $(BUILD_DIR)$(GODOT)


graphique: $(PATH_GODOT)

.PHONY : all server graphique
