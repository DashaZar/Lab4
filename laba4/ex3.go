package main

import (
	"fmt"
	"os"
)

func generateSequence(x0, a, b, c int64) {
	sequence := []int64{x0}       // Хранит всю последовательность
	seen := make(map[int64]int)   // Хранит значение и его индекс
	seen[x0] = 0                  // Начальное значение

	var cycleStart, cycleLength int
	cycleFound := false
	maxIterations := 1000

	// Генерация последовательности
	for i := 1; i < maxIterations; i++ {
		next := (a*sequence[i-1] + b) % c
		sequence = append(sequence, next)

		// Проверка на повторение
		if idx, exists := seen[next]; exists {
			cycleStart = idx
			cycleLength = i - idx
			cycleFound = true
			break
		}
		seen[next] = i
	}

	// Обработка результатов
	if cycleFound {
		// Догенерация до двух полных циклов
		targetSize := cycleStart + cycleLength*2
		for len(sequence) < targetSize && len(sequence) < maxIterations {
			next := (a*sequence[len(sequence)-1] + b) % c
			sequence = append(sequence, next)
		}

		// Вывод последовательности
		fmt.Print("Сгенерированная последовательность: ")
		for i := 0; i < targetSize && i < len(sequence); i++ {
			fmt.Printf("%d ", sequence[i])
		}
		fmt.Println()

		// Индекс начала повторения (1-based)
		fmt.Printf("Индекс начала повторения: %d\n", cycleStart+cycleLength+1)
	} else {
		fmt.Printf("Цикл не найден за %d итераций.\n", maxIterations)
		fmt.Print("Сгенерированная последовательность: ")
		for _, v := range sequence {
			fmt.Printf("%d ", v)
		}
		fmt.Println()
	}
}

func main() {
	var x0, a, b, c int64

	// Ввод параметров
	fmt.Print("Введите начальное значение X0 (0 <= X0 < C): ")
	fmt.Scan(&x0)

	fmt.Print("Введите множитель A (0 <= A <= C): ")
	fmt.Scan(&a)

	fmt.Print("Введите инкремент B (0 <= B <= C): ")
	fmt.Scan(&b)

	fmt.Print("Введите модуль C (C > 0): ")
	fmt.Scan(&c)

	// Проверка корректности
	if c <= 0 || x0 < 0 || x0 >= c || a < 0 || a > c || b < 0 || b > c {
		fmt.Println("Ошибка: Некорректные входные данные!")
		os.Exit(1)
	}

	generateSequence(x0, a, b, c)
}
