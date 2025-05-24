package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

// Borda winners calculation
func bordaWinners(prefs [][]int, n int) []int {
	scores := make([]int, n)
	for _, ranking := range prefs {
		for pos, candidate := range ranking {
			scores[candidate] += n - 1 - pos
		}
	}

	maxScore := 0
	for _, score := range scores {
		if score > maxScore {
			maxScore = score
		}
	}

	winners := []int{}
	for i, score := range scores {
		if score == maxScore {
			winners = append(winners, i)
		}
	}
	return winners
}

// Check Condorcet winner
func isCondorcetWinner(c int, prefs [][]int, n, k int) bool {
	for other := 0; other < n; other++ {
		if other == c {
			continue
		}

		wins := 0
		for _, ranking := range prefs {
			cPos := indexOf(ranking, c)
			otherPos := indexOf(ranking, other)
			if cPos < otherPos {
				wins++
			}
		}

		if wins <= k/2 {
			return false
		}
	}
	return true
}

func condorcetWinner(prefs [][]int, n, k int) int {
	for c := 0; c < n; c++ {
		if isCondorcetWinner(c, prefs, n, k) {
			return c
		}
	}
	return -1
}

// Helper function to find index
func indexOf(slice []int, val int) int {
	for i, v := range slice {
		if v == val {
			return i
		}
	}
	return -1
}

func main() {
	reader := bufio.NewReader(os.Stdin)

	var n, k int
	fmt.Print("Введите количество кандидатов (n): ")
	fmt.Scan(&n)
	fmt.Print("Введите количество избирателей (k): ")
	fmt.Scan(&k)
	reader.ReadString('\n') // Clear buffer

	// Read candidates
	candidates := make([]string, n)
	candidateMap := make(map[string]int)
	fmt.Println("Введите имена кандидатов (как есть, без нормализации):")
	for i := 0; i < n; i++ {
		fmt.Printf("Кандидат %d: ", i+1)
		name, _ := reader.ReadString('\n')
		name = strings.TrimSpace(name)
		
		if _, exists := candidateMap[name]; exists {
			fmt.Fprintf(os.Stderr, "Ошибка: Кандидат '%s' уже существует!", name)
			os.Exit(1)
		}
		
		candidates[i] = name
		candidateMap[name] = i
	}

	// Read preferences
	prefs := make([][]int, k)
	fmt.Printf("\nВведите предпочтения (%d имен через пробел):\n", n)
	for i := 0; i < k; i++ {
		for {
			fmt.Printf("Избиратель %d: ", i+1)
			input, _ := reader.ReadString('\n')
			input = strings.TrimSpace(input)
			names := strings.Fields(input)

			if len(names) != n {
				fmt.Printf("Ошибка: Нужно %d кандидатов!\n", n)
				continue
			}

			valid := true
			votes := make([]int, n)
			unique := make(map[int]bool)
			
			for j, name := range names {
				if idx, exists := candidateMap[name]; exists {
					if unique[idx] {
						fmt.Println("Ошибка: Повторы в списке!")
						valid = false
						break
					}
					votes[j] = idx
					unique[idx] = true
				} else {
					fmt.Printf("Ошибка: Неизвестный кандидат '%s'\n", name)
					valid = false
					break
				}
			}

			if valid {
				prefs[i] = votes
				break
			}
		}
	}

	// Calculate results
	borda := bordaWinners(prefs, n)
	condorcet := condorcetWinner(prefs, n, k)

	// Print results
	fmt.Println("\nРезультаты:")
	fmt.Print("Метод Борда: ")
	if len(borda) == 1 {
		fmt.Println(candidates[borda[0]])
	} else {
		fmt.Print("Ничья между: ")
		for i, idx := range borda {
			fmt.Printf("'%s'", candidates[idx])
			if i < len(borda)-1 {
				fmt.Print(", ")
			}
		}
		fmt.Println()
	}

	fmt.Print("Метод Кондорсе: ")
	if condorcet != -1 {
		fmt.Println(candidates[condorcet])
	} else {
		fmt.Println("Нет победителя")
	}

	// Check for different winners
	if condorcet != -1 {
		found := false
		for _, c := range borda {
			if c == condorcet {
				found = true
				break
			}
		}
		if !found {
			fmt.Println("\n⚠️ Методы дали разных победителей!")
		}
	}
}
