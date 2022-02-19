	Pour utiliser mon programme il faudra git clone via l'URL GitHub.

	Une fois installé il suffira d'ouvrir le fichier TP1_IA.ueproject (Unreal Engine Project File) dans le dossier TP-Steer.

	Logiquement un message s'affichera sur l'écran afin de générer les fichiers manquants trop volumineux pour GitHub que 
j'ai donc du mentionner dans le .gitignore

	Une fois terminé , Unreal Editor va s'ouvrir et le TP sera visible. En revanche mes 4 class C++ ne pourront pas être ouvertes
avec Visual Studio 2019 pour l'instant.

	Pour pouvoir les lire il faudra clique droit sur le fichier TP1_IA.ueproject et cliquer sur " Generate Visual Studio project files"
afin de créer le fichier .sln qui permettra d'ouvrir les fichiers .h et .cpp

	Le projet est donc maintenant entièrement chargé/téléchargé.



Sur l'écran il y a :

- Une capsule rouge qui représente le joueur.
	Z pour avancer
	S pour reculer			( le personnage tourne difficilement , il ne faut pas hésiter à appuyer plusieurs 
	D pour tourner à droite			 fois et laisser enfoncer pour mieux se déplacer)
	Q pour tourner à gauche	

- Une flèche bleu qui représente l'IA qui contient les algos de Seek, Flee , Arrival , Pursuit et Evade.
	Space pour changer d'algo ( Seek inialement )

- Trois flèches vertes 
	- la plus petite va suivre un Circuit

	- la moyenne va suivre l'algo Two Path

	- la plus grande va suivre l'algo One Path

	Pour le lancer il suffit de cliquer sur l'icone Play en haut à droite et pour pouvoir déplacer le joueur il faut clique gauche.




Pour ce qui est de l'organisation :

Le dossier "Content" contient 4 dossiers :

	- "Blueprint" qui contient les 4 BP dont j'ai eu besoin
	- "Maps" qui contient la MainMap
	- "Mats" qui contient les matériaux que j'ai créé pour différencier les objets
	- "StarterContent" qui contient du contenu de base

Dans C++ Classes se situe simplement mes 4 class C++

Et pour finir dans le "World Outliner" en haut à droite on peut trouver :
	- 1 dossier Véhicules qui contient les 5 véhicules
	- 1 dossier Waypoints contenant tous mes waypoint
	- la caméra
	- la lumière
	- le sol
  