<h1 align="left">🪡 Hangman (Pendu)</h1>

<p align="left">Ce projet est un jeu du pendu développé en Golang. L'objectif du jeu est de trouver toutes les lettres d'un mot en moins de 10 essais. Ce jeu comporte différents modes de jeu.</p>

###

<h2 align="left">✨ Fonctionnalités</h2>

-  Un mode classique
-  Un mode hardcore (moins d'essais, moins de lettres...)
-  Un système de sauvegarde 
-  Une customisation des mots présents dans le jeu

###

<h2 align="left">🕹️ Utilisation</h2>

<p align="left">Pour lancer le jeu, entrez la commande suivante :</p>

<div align="left">
  <img height="30" src="https://cdn.discordapp.com/attachments/1292839304439267390/1308510006328430715/image.png?ex=673e3468&is=673ce2e8&hm=24725c5a8678732d97c2823624e3bda63e2a12740da266cc0aa2fab90a9592ec&"  />
</div>

###

<p aligne="left"> Les lettres à accent ne sont pas disponibles dans le jeu. </p>


###

<h2 align="left">💾 Sauvegarde</h2>

<p align="left">Vous pouvez sauvegarder votre partie à tout moment en tapant "STOP".</p>
<p align="left">Pour charger votre partie précédente, relancez le jeu et une nouvelle ligne dans le menu du jeu vous propose de charger votre partie précédente.</p>
<p align="left"> **Attention, si vous finissez une partie dans n'importe quel mode de jeu avec une autre partie sauvegardé, la sauvegarde sera supprimée.**

###

<h2 align="left">🎁 Customisation </h2>

<p align="left">Vous pouvez rajouter autant de mots que vous voulez dans les fichiers suivant : </p>
<div align="left">
  <img height="80" src="https://cdn.discordapp.com/attachments/1292839304439267390/1308735862992932884/image.png?ex=673f06c0&is=673db540&hm=4fed6f182feea428dfe8971fd3fe1464af9a1d2a4879dd1bf5676e930f5f0ae5&"/>
</div>

###

<p align="left">Mais faites attention, les mots avec des accents ne seront pas utilisable dans le jeu !

###

<h2 align="left">📂 Arborescence </h2>

<div align = "left">
  <img height="300" src="https://cdn.discordapp.com/attachments/1292839304439267390/1308789175968858153/image.png?ex=673f3867&is=673de6e7&hm=2230a221e6491d2d9d15b5d9e716e53efec9b2403737e27ff3c3ba1e2176d1b8&">
</div>

###

<h2 align="left">📀 Fichiers du jeu </h2>

- menu.go : Sert à afficher le menu du jeu quand on le lance.
- mots.go : Sert à choisir un mot aléatoire dans les 3 fichiers précisés dans le code. Pour changer un fichier de mot, il doit obligatoirement avoir le nom words.txt/words2.txt ou word3.txt.
- words.txt/words2.txt/words3.txt : Contiennent les mots qui servent dans le jeu.
- revele.go : Fonctionnement général du jeu. Gère les modes de jeu, l'affichage du texte, des positions du pendu, gère les lettres à rentrer et à afficher, gère la victoire ou défaite du joueur.
- stades.go : Contient toutes les positions du pendu sous forme d'une fonction appelable dans les autres fichiers.
- go.mod : Module hangman du projet
- main.go : Lancement du jeu

###

<h2 align="left">🎮 Déroulement du jeu </h2>

<div align="left">
  <img height="200" src="https://cdn.discordapp.com/attachments/1292839304439267390/1308796134772441088/image.png?ex=673f3ee2&is=673ded62&hm=d867c46c1ebad033a25fcdf640ef7c000b06a04828524f84b8bd7aac7b45dbd5&">
</div>

###

<h2 align="left">📇 Prochaines améliorations </h2>

- Ajouter un nouveau mode de jeu pour permettre de joueur avec des lettres en art Ascii
- Ajouter la possibilité au joueur d'entrer des lettres avec accent
- Ajouter la possibilité de jouer avec des mots à espaces
- Optimiser le code pour le rendre plus rapide

###

<h2 align="left">👨‍💻 Auteurs </h2>

- Evan Husser
- Julie Lefebvre
- Maimouna Maide Hangatta


