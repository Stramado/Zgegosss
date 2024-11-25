package menu

import (
	"fmt"
	"os"
)

func Menu() int {

	fmt.Print("\nBienvenue dans le jeu du pendu !\n")

	for {
		fmt.Print("\n-----------------------------------------------------------------\n")
		fmt.Print("\n[1] Lancer le jeu en version classique\n")
		fmt.Print("[2] Lancer le jeu en version hardcore\n")

		_, err := os.Stat("save.txt")

		if !os.IsNotExist(err) { // Proposition de charger une sauvegarde que si un fichier de save existe
			fmt.Print("[3] Charger une sauvegarde\n")
		}

		fmt.Print("\nQue voulez-vous faire ? : ")
		var input string
		fmt.Scan(&input)

		switch input {
		case "1":
			return 1
		case "2":
			return 2
		case "3":
			if !os.IsNotExist(err) { // Vérification que fichire de save existe
				return 3
			}
		default:
			fmt.Print("\nEntrez un numéro\n")
			continue
		}
	}
}
