package mots

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"strings"
	"time"
)

func Mots() string {
	rand.Seed(time.Now().UnixNano())
	NumFichier := 0
	var words []string
	NumMots := 0

	for { // Choix du fichier qui sera choisit pour le mot que le joueur devra devenier
		NumFichier = rand.Intn(4)
		if NumFichier == 1 { // Fichier 1
			file, err := os.Open("mots/words.txt") // Stockge de toutes les valeurs du fichier dans une variable
			if err != nil {
				fmt.Println("Error: ", err)
				return ""
			}
			defer file.Close()

			scanner := bufio.NewScanner(file) // Scan du nombre de lignes présentes dans le fichier
			for scanner.Scan() {
				words = append(words, scanner.Text()) // Ajout du mot aléatoire présent dans le fichier dans une variable qui sera renvoyé par la fonction
			}

			if err := scanner.Err(); err != nil {
				fmt.Println("Error reading file:", err)
			}
			NumMots = len(words)
			break
		}

		if NumFichier == 2 { // Fichier 2
			file, err := os.Open("mots/words2.txt") // Stockge de toutes les valeurs du fichier dans une variable
			if err != nil {
				fmt.Println("Error: ", err)
				return ""
			}
			defer file.Close()

			scanner := bufio.NewScanner(file) // Scan du nombre de lignes présentes dans le fichier
			for scanner.Scan() {
				words = append(words, scanner.Text()) // Ajout du mot aléatoire présent dans le fichier dans une variable qui sera renvoyé par la fonction
			}

			if err := scanner.Err(); err != nil {
				fmt.Println("Error reading file:", err)
			}
			NumMots = len(words)
			break
		}

		if NumFichier == 3 { // Fichier 3
			file, err := os.Open("mots/words3.txt") // Stockge de toutes les valeurs du fichier dans une variable
			if err != nil {
				fmt.Println("Error: ", err)
				return ""
			}
			defer file.Close()

			scanner := bufio.NewScanner(file) // Scan du nombre de lignes présentes dans le fichier
			for scanner.Scan() {
				words = append(words, scanner.Text()) // Ajout du mot aléatoire présent dans le fichier dans une variable qui sera renvoyé par la fonction
			}

			if err := scanner.Err(); err != nil {
				fmt.Println("Error reading file:", err)
			}
			NumMots = len(words)
			break
		}
	}

	motChoisit := rand.Intn(NumMots + 1)

	if motChoisit == NumMots+1 {
		words[motChoisit-2] = strings.ToLower(words[motChoisit-2])
		return words[motChoisit-2] // La fonction renvoie un mot aléatoire dans un des 3 fichiers
	}

	if motChoisit == NumMots {
		words[motChoisit-1] = strings.ToLower(words[motChoisit-1])
		return words[motChoisit-1] // La fonction renvoie un mot aléatoire dans un des 3 fichiers
	}
	words[motChoisit] = strings.ToLower(words[motChoisit])
	return words[motChoisit] // La fonction renvoie un mot aléatoire dans un des 3 fichiers

}
