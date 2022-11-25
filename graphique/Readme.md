# Graphique Zappy

Godot 3.4.2

## Architecture

- Assets
- fonts
- Scene
- Script
- Texture
- Theme : all theme for interface

### Scripts
- Camera_lvl.gd : main camera
- Client.gd : connected socket
- CommandServer.gd : all command to call API
- Level.gd : display
- Main.gd : just main

# API

## MAP

### map_add_gem(arr: Array) -> void
Args:
- arr : tableau contenant les gemmes pour un block

### map_set(x: int, z: int) -> void
Args:
- x : taille de x
- z : taille de z

Ajout d'une nouvelle map

## HUD

### hud_message_server(msg: String) -> void
Arg:
- msg : envoyer un message appartenant au serveur

### hud_add_team(id_team: String) -> void
Arg:
- id_team : nom de la team

Ajout d'une nouvelle team sur l'HUD

## Player

### player_die(id_player: String) -> void
Arg:
- id_player : nom du joueur

Un joueur est mort

### player_kicked(id_player: String) -> void
Arg:
- id_player : nom du joueur

Un joueur est kick

### player_fork_start(id_player: String) -> void
Arg:
- id_player : nom du joueur

Un joueur commence un fork

### player_broadcast(id_player: String, msg: String) -> void
Args:
- id_player : nom du joueur
- msg : message

Un joueur envoie un message

### player_level(id_player: String, level: int) -> void
Args:
- id_player : nom du joueur
- level : le nouveau niveau du joueur

Un joueur a change de niveau

### player_incantation(arr_player: Array) -> void
Arg:
- arr_player: tableau de nom de joueur

Un nombre de joueur lance une incantation

### player_putdown_item(id_player: String, color_gem: int) -> void
Args:
- id_player : nom du joueur
- color_gem : numero de la gemme

Un joueur pose une gemme

### player_pickup_item(id_player: String, color_gem: int) -> void
Args:
- id_player : nom du joueur
- color_gem : numero de la gemme

Un joueur prend une gemme

### player_move(id_player: String, vec: Vector3, orientation: int, time: float) -> void
Args:
- id_player : nom du joueur
- vec : nouveau emplacement
- orientation : nouvelle orientation du joueur
- time : temps serveur

Un joueur se deplace

### player_add_new(id_player: String, position: Vector3, orientation: int, level: int, team: String, time: float) -> void
Args:
- id_player : nom du joueur
- position : emplacement du nouveau joueur
- orientation : orientation du nouveau joueur
- level : level du joueur
- team : nom de la team du joueur
- time : temps serveur

Ajout d'un nouveau joueur

## Egg

### egg_die(id_egg: String) -> void
Arg:
- id_egg : nom de l'oeuf

Un oeuf meurt

### egg_spawn(id_egg: String, id_player: String, position: Vector3) -> void
Args:
- id_egg : nom de l'oeuf
- id_player : nom du joueur a qui appartient l'oeuf
- position : emplacement de l'oeuf

Ajout d'un nouvel oeuf sur la map

## Game over

### game_over(name_team: String) -> void
Arg:
- name_team : nom de la team gagnante

Fin du jeu
