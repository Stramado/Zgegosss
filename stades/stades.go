package stades

import "fmt"

func Position1() {
	fmt.Print("\n ========= \n")
	fmt.Print("\n")
}

func Position2() {
	fmt.Print("\n")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("=========")
	fmt.Print("\n")
}

func Position3() {
	fmt.Print("\n")
	fmt.Println("   +---+")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("=========")
	fmt.Print("\n")
}

func Position4() {
	fmt.Print("\n")
	fmt.Println("   +---+")
	fmt.Println("   |   |")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("=========")
	fmt.Print("\n")
}

func Position5() {
	fmt.Print("\n")
	fmt.Println("   +---+")
	fmt.Println("   |   |")
	fmt.Println("   O   |")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("=========")
	fmt.Print("\n")
}

func Position6() {
	fmt.Print("\n")
	fmt.Println("   +---+")
	fmt.Println("   |   |")
	fmt.Println("   O   |")
	fmt.Println("   |   |")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("=========")
	fmt.Print("\n")
}

func Position7() {
	fmt.Print("\n")
	fmt.Println("   +---+")
	fmt.Println("   |   |")
	fmt.Println("   O   |")
	fmt.Println("  /|   |")
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("=========")
	fmt.Print("\n")
}

func Position8() {
	var backslash rune = 92
	fmt.Print("\n")
	fmt.Println("   +---+")
	fmt.Println("   |   |")
	fmt.Println("   O   |")
	fmt.Printf("  /|%v  |\n", string(backslash))
	fmt.Println("       |")
	fmt.Println("       |")
	fmt.Println("=========")
	fmt.Print("\n")
}

func Position9() {
	var backslash rune = 92
	fmt.Print("\n")
	fmt.Println("   +---+")
	fmt.Println("   |   |")
	fmt.Println("   O   |")
	fmt.Printf("  /|%v  |\n", string(backslash))
	fmt.Printf("  /    |\n")
	fmt.Println("       |")
	fmt.Println("=========")
	fmt.Print("\n")
}

func Position10() {
	var backslash rune = 92
	fmt.Print("\n")
	fmt.Println("   +---+")
	fmt.Println("   |   |")
	fmt.Println("   O   |")
	fmt.Printf("  /|%v  |\n", string(backslash))
	fmt.Printf("  / %v  |\n", string(backslash))
	fmt.Println("       |")
	fmt.Println("=========")
	fmt.Print("\n")
}
