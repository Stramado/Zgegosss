package revele

import (
	"encoding/json"
	"fmt"
	"hangman/menu"
	"hangman/mots"
	"hangman/stades"
	"math/rand"
	"os"
	"strings"
	"time"
)

type PlayerData struct {
	Attemps      int      `json:"Tentatives: "`
	Mot          string   `json:"Word: "`
	Letters      []string `json:"Letters found: "`
	LettersUsed  []string `json:"Letter used by player: "`
	LettersP     []rune   `json:"LettersP"`
	LettersUsedP []rune   `json:"LettersUsedP"`
	HardcoreMode bool     `json:"Hardmode: "`
}

var GameDat PlayerData
var wordToFind string = mots.Mots()           // Mot à trouver
var SplitWord = strings.Split(wordToFind, "") // Le mot à trouver sous forme d'un tableau
var reveleSave []string                       // Le mot sous forme de _ en tableau de string pour la save
var revelePlayer []rune                       // Le mot sous forme de _ en tableau de rune pour l'affichage du jeu
var usedLettersSave []string                  // Tableau pour les lettres déjà utilisés pour la save
var usedLettersPlayer []rune                  // Tableau pour les lettres déjà utilisés pour l'afficahge du jeu
var Hardmode bool                             // Si le joueur est en mode classique ou en hardmode

func InitialisePlayerData() { // Initialiser les données du joueur

	reveleSave = make([]string, len(wordToFind)) // Création tableau de la taille du mot pour la save
	revelePlayer = make([]rune, len(wordToFind)) // Création tableau pour l'affichage dans le jeu

	for i := range wordToFind { // Pour mettre le mot sous forme de _ pour la save et l'affichage
		reveleSave[i] = "_"
		revelePlayer[i] = '_'
	}

	usedLettersSave = []string{}
	usedLettersPlayer = []rune{}

	GameDat = PlayerData{ // Valeurs utilisés dans le jeu
		Attemps:      10,
		Mot:          wordToFind,
		Letters:      reveleSave,
		LettersUsed:  usedLettersSave,
		LettersP:     revelePlayer,
		LettersUsedP: usedLettersPlayer,
		HardcoreMode: false, // Si hardmode actif ou pas
	}
}

func Revele() { // Initialiser ou charger le jeu
	choixModeJeu := menu.Menu() // Affichage du menu principal du jeu
	if choixModeJeu == 1 {      // Mode de jeu classique
		InitialisePlayerData()
		ShowingLetters()
		GameLoop()
	}
	if choixModeJeu == 2 { // Mode hardcore
		Hardmode = true
		fmt.Print("\nDans ce mode de jeu, moins de lettres s'affichent au début du jeu, chaque erreur vous fait perdre 2 essais, vous ne pouvez utiliser que 3 voyelles et vos lettres déjà utilisés ne s'affichent pas.\n")
		fmt.Print("Bonne chance ;)\n")
		InitialisePlayerData()
		ShowingLetters()
		GameLoop()
	}
	if choixModeJeu == 3 { // Si un fichier de sauvegarde a été trouvé, si la moindre erreur apparait lors du chargement des données, un partie classqiue est lancée
		err := OpenSave() // Chargement de la partie précédente
		if err != nil {   // Si une erreur lors du chargement des données, une partie classique est lancée
			fmt.Println("Erreur lors du chargement de la sauvegarde:", err)
			fmt.Println("Une nouvelle partie va commencer.")
			InitialisePlayerData()
			ShowingLetters() // Affichage de quelques lettres dans le mot
			GameLoop()
		} else {
			GameLoop()
		}
	}

}

func OpenSave() error { // Charger la sauvegarde
	fileData, err := os.ReadFile("save.txt") // Stocker toutes les valeurs du fichier de save dans une variable
	if err != nil {
		return err
	}

	var tempData PlayerData                   // Variable pour stocker temporairement les données du fichier
	err = json.Unmarshal(fileData, &tempData) // Décodage des données du fichier
	if err != nil {
		return fmt.Errorf("erreur lors du décodage JSON: %v", err)
	}

	// Ajuster la taille des tableaux pour éviter que le mot soit plus grand que le tableau contenant ses lettres
	if len(tempData.Letters) != len(tempData.Mot) {
		tempData.Letters = make([]string, len(tempData.Mot)) // Save
	}
	if len(tempData.LettersP) != len([]rune(tempData.Mot)) {
		tempData.LettersP = make([]rune, len([]rune(tempData.Mot))) // Joueur
	}
	if len(tempData.LettersUsedP) > len(tempData.Mot) {
		tempData.LettersUsedP = tempData.LettersUsedP[:len(tempData.Mot)]
	}

	for i := range tempData.Letters { // Réinitialiser les lettres cachées si nécessaire car parfois les _ disparaissent
		if tempData.Letters[i] == "" {
			tempData.Letters[i] = "_"
			tempData.LettersP[i] = '_'
		}
	}

	GameDat = tempData // Assignation des valeurs du fichier vers la structure contenant les données du jeu
	return nil
}

func ShowingLetters() { // Révéler certaines lettres au début du jeu
	var nbLettersToReveal int

	if len(GameDat.Mot) == 0 { // Vérification si un mot a été choisit sinon err
		fmt.Println("Erreur: Le mot est vide. Impossible de continuer.")
		return
	}

	if Hardmode {
		nbLettersToReveal = int((float64(len(GameDat.Mot)) / 3) - 1) // Calcul du nombre de lettres à afficher
	} else {
		nbLettersToReveal = int((float64(len(GameDat.Mot)) / 2) - 1)
	}

	if nbLettersToReveal <= 0 {
		nbLettersToReveal = 1 // Au moins 1 lettre doit être affichée
	}

	revealedIndices := map[int]bool{0: true}
	rand.Seed(time.Now().UnixNano())

	for k := 0; k < nbLettersToReveal; k++ { // Affichage des lettres aléatoires
		for {
			randIndex := rand.Intn(len(GameDat.Mot))

			if _, exists := revealedIndices[randIndex]; !exists { // Vérifie si la lettre n'a pas déjà été affiché
				revealedIndices[randIndex] = true
				GameDat.Letters[randIndex] = string([]rune(GameDat.Mot)[randIndex])
				GameDat.LettersP[randIndex] = []rune(GameDat.Mot)[randIndex]
				break
			}
		}
	}
}

func GameLoop() { // Boucle du jeu
	HardNbVowels := 3                              // Nombre de voyelle que le joueur peut utiliser si il est en hardmode
	Vowels := []rune{'a', 'e', 'i', 'o', 'u', 'y'} // Liste des voyelles
	OverVowel := false
	accents := []string{"é", "è", "ê", "à", "â", "ç", "ù", "û", "î", "ô", "ä", "ë", "ï", "ü", "ö", "ÿ"}

	for GameDat.Attemps > 0 {
		fmt.Print("\n----------------------------------------------------\n")
		if Hardmode {
			fmt.Print("\nMode hardcore activé\n")
		}
		fmt.Println("\nMot:", strings.Join(GameDat.Letters, " "))
		fmt.Printf("Tentatives restantes: %d\n", GameDat.Attemps)
		if !Hardmode { // Les lettres entrées ne s'affichent pas en hardmode
			fmt.Println("Lettres incorrectes :", string(GameDat.LettersUsedP))
		}

		fmt.Print("\nDevinez une lettre: ")
		var proposition string
		fmt.Scan(&proposition)

		for i := 0; i < len(accents); i++ {
			if proposition == accents[i] {
				i = 0
				fmt.Print("\n La lettre ne doit pas contenir d'accent\n")
				fmt.Print("\nDevinez une lettre: ")
				fmt.Scan(&proposition)
			}
		}

		if proposition == "STOP" { // Si le joueur veut sauvegarder
			err := SaveGame()
			if err != nil {
				fmt.Println("Erreur lors de la sauvegarde:", err)
			} else {
				fmt.Println("Vous avez sauvegardé votre progression")
				time.Sleep(3 * time.Second)
			}
			return
		}

		if len(proposition) != 1 { // Si le joueur entre plus de 1 charactère
			if proposition == GameDat.Mot { // Si le mot entré est le bon, le joueur gagne
				WinOrLose(true)
				return
			} else { // Sinon il perd 2 essais ou 3 essais si il est en mode hardcore
				if Hardmode {
					GameDat.Attemps -= 3
					fmt.Println("Mot incorrect, -3 essais")
				} else {
					GameDat.Attemps -= 2
					fmt.Println("Mot incorrect, -2 essais")
				}
				DrawHangman()
			}
		} else {
			lettre := rune(proposition[0])
			if lettre >= 65 && lettre <= 90 { // Si la lettre entrée est en majuscule, elle est convertie en minuscule
				lettre = lettre + 32
			}

			if Hardmode { // Vérification si le joueur a entré une voyelle
				for i := 0; i < len(Vowels); i++ {
					if lettre == Vowels[i] {
						HardNbVowels--                                // Si il reste des voyelles utilisable par le joueur, son nombre est décompté
						if lettre == Vowels[i] && HardNbVowels <= 0 { // Si le joueur n'a plus de voyelles utilisables, la lettre entrée est compté comme fausse
							OverVowel = true
							fmt.Print("\nVous avez utilisé toutes vos voyelles.\n")
						}
					}
				}
			}
			if !strings.ContainsRune(GameDat.Mot, lettre) { // Vérification si la lettre est dans le mot
				if !ContainsRune(GameDat.LettersUsedP, lettre) { // Si elle n'y est pas, -1 essai
					if Hardmode {
						GameDat.Attemps -= 2
					} else {
						GameDat.Attemps--
					}
					if !Hardmode {
						GameDat.LettersUsed = append(GameDat.LettersUsed, proposition) // Ajout lettre dans la liste des lettres déjà utilisés save
						GameDat.LettersUsedP = append(GameDat.LettersUsedP, lettre)    // Ajout lettre dans la lliste des lettres déjà utilisés joueur
					}

					if Hardmode && !OverVowel {
						fmt.Println("Lettre incorrecte")
					}

					DrawHangman() // Affichage position du pendu
				} else if !Hardmode {
					fmt.Println("Lettre déjà utilisée")
				}
			} else if !OverVowel {
				for i, c := range GameDat.Mot { // Ajout de la lettre dans le mot si elle est correct en remplacant un _ par la lettre
					if c == lettre {
						GameDat.Letters[i] = string(c) // Save
						GameDat.LettersP[i] = c        // Joueur
					}
				}

				if strings.Join(GameDat.Letters, "") == GameDat.Mot { // Si le joueur à trouvé toutes les lettres, il gagne
					WinOrLose(true)
					return
				}

			}
			OverVowel = false

		}
	}
	WinOrLose(false) // Si toutes les tentatives ont été utilisé, le joueur perd
}

func DrawHangman() { // Positions du pendu
	switch GameDat.Attemps {
	case 9:
		stades.Position1()
	case 8:
		stades.Position2()
	case 7:
		stades.Position3()
	case 6:
		stades.Position4()
	case 5:
		stades.Position5()
	case 4:
		stades.Position6()
	case 3:
		stades.Position7()
	case 2:
		stades.Position8()
	case 1:
		stades.Position9()
	case 0:
		stades.Position10()
	}
}

func SaveGame() error { // Sauvegarde des données au format json
	fileData, err := json.Marshal(GameDat)
	if err != nil {
		return err
	}
	return os.WriteFile("save.txt", fileData, 0644)
}

func WinOrLose(result bool) { // Condition de victoire ou défaite
	if result {
		fmt.Println("Félicitations! Vous avez trouvé le mot:", GameDat.Mot)
		time.Sleep(3 * time.Second)
	} else {
		fmt.Println("Dommage! Vous n'avez plus de tentatives. Le mot était:", GameDat.Mot)
		time.Sleep(3 * time.Second)
	}
	os.Remove("save.txt") // Quand la partie est finie, si un fichier de save est présent, il est supprimé
}

func ContainsRune(tab []rune, r rune) bool { // Vérifie si une lettre est présejte dans le mot
	for _, v := range tab {
		if v == r {
			return true
		}
	}
	return false
}
