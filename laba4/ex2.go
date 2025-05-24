package main

import (
	"fmt"
	"math/rand"
	"time"
	"math"
)

func main() {
	rand.Seed(time.Now().UnixNano())

	// Задание 1
	fmt.Println("=== Задание 1 ===")
	var n int
	for {
		fmt.Print("Введите размер массива (n >= 20): ")
		fmt.Scan(&n)
		if n >= 20 {
			break
		}
	}

	arr := make([]int, n)
	for i := range arr {
		arr[i] = rand.Intn(501) - 250 // Генерация чисел от -250 до 250
	}

	fmt.Println("Сгенерированный массив:")
	printSlice(arr)
	fmt.Println()

	// Задание 2
	fmt.Println("=== Задание 2 ===")
	negativeCount := 0
	minAbsValue := math.Abs(float64(arr[0]))
	minAbsIndex := 0

	for i, v := range arr {
		if v < 0 {
			negativeCount++
		}

		if abs := math.Abs(float64(v)); abs < minAbsValue {
			minAbsValue = abs
			minAbsIndex = i
		}
	}

	sumAfterMin := 0
	for i := minAbsIndex + 1; i < len(arr); i++ {
		sumAfterMin += int(math.Abs(float64(arr[i])))
	}

	fmt.Printf("Количество отрицательных элементов: %d\n", negativeCount)
	fmt.Printf("Сумма модулей после минимального по модулю элемента: %d\n\n", sumAfterMin)

	// Задание 3
	fmt.Println("=== Задание 3 ===")
	maxLen, currentLen := 1, 1
	startIdx, endIdx := 0, 0
	currentStart := 0

	for i := 1; i < len(arr); i++ {
		if arr[i] < arr[i-1] {
			currentLen++
			if currentLen > maxLen {
				maxLen = currentLen
				startIdx = currentStart
				endIdx = i
			}
		} else {
			currentLen = 1
			currentStart = i
		}
	}

	fmt.Println("Самая длинная убывающая последовательность:")
	fmt.Printf("Индексы: [%d - %d]\n", startIdx, endIdx)
	fmt.Print("Элементы: ")
	printSlice(arr[startIdx : endIdx+1])
	fmt.Println("\n")

	// Задание 4
	fmt.Println("=== Задание 4 ===")
	reversedSeq := make([]int, maxLen)
	for i := 0; i < maxLen; i++ {
		reversedSeq[i] = arr[endIdx-i]
	}

	fmt.Println("Перевернутая последовательность:")
	printSlice(reversedSeq)
	fmt.Println("\n")

	// Задание 5
	fmt.Println("=== Задание 5 ===")
	var m, k int

	for {
		fmt.Print("Введите размер первого массива (m > 0): ")
		fmt.Scan(&m)
		if m > 0 {
			break
		}
	}

	for {
		fmt.Print("Введите размер второго массива (k > 0): ")
		fmt.Scan(&k)
		if k > 0 {
			break
		}
	}

	arr1 := make([]int, m)
	arr2 := make([]int, k)
	for i := range arr1 {
		arr1[i] = rand.Intn(501) - 250
	}
	for i := range arr2 {
		arr2[i] = rand.Intn(501) - 250
	}

	fmt.Println("\nПервый массив до:")
	printSlice(arr1)
	fmt.Println("\nВторой массив до:")
	printSlice(arr2)
	fmt.Println("\n")

	if len(arr1) > 0 && len(arr2) > 0 {
		last1 := arr1[len(arr1)-1]
		last2 := arr2[len(arr2)-1]

		arr1 = arr1[:len(arr1)-1]
		arr2 = arr2[:len(arr2)-1]

		arr1 = append([]int{last2}, arr1...)
		arr2 = append([]int{last1}, arr2...)
	}

	fmt.Println("Первый массив после:")
	printSlice(arr1)
	fmt.Println("\nВторой массив после:")
	printSlice(arr2)
	fmt.Println()
}

func printSlice(s []int) {
	for _, v := range s {
		fmt.Printf("%d ", v)
	}
}

