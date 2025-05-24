package main

import (
	"fmt"
	"math"
)

const epsilon = 0.0001 // Точность

// Функция f(x) = sin(x) - 2x - 1
func f(x float64) float64 {
	return math.Sin(x) - 2*x - 1
}

// Производная f'(x) = cos(x) - 2
func df(x float64) float64 {
	return math.Cos(x) - 2
}

// Функция итерации phi(x) = (sin(x) - 1)/2
func phi(x float64) float64 {
	return (math.Sin(x) - 1) / 2
}

// Метод половинного деления
func bisection(a, b float64) (float64, int, error) {
	if f(a)*f(b) >= 0 {
		return 0, 0, fmt.Errorf("invalid interval for bisection method")
	}
	
	var c float64
	iter := 0
	fmt.Println("BISECTION METHOD")
	fmt.Printf("%2s | %9s | %9s | %9s\n", "N", "a", "b", "b-a")
	
	for math.Abs(b-a) >= epsilon {
		c = (a + b) / 2
		fmt.Printf("%2d | %9.4f | %9.4f | %9.4f\n", iter, a, b, b-a)
		
		if f(c) == 0 {
			break
		}
		
		if f(c)*f(a) < 0 {
			b = c
		} else {
			a = c
		}
		iter++
	}
	fmt.Printf("Root: %.4f found in %d iterations\n", c, iter)
	return c, iter, nil
}

// Метод Ньютона
func newton(x0 float64) (float64, int) {
	iter := 0
	x1 := x0 - f(x0)/df(x0)
	fmt.Println("\nNEWTON'S METHOD")
	fmt.Printf("%2s | %9s | %9s | %9s\n", "N", "xₙ", "xₙ₊₁", "Δx")
	
	for math.Abs(x1-x0) > epsilon {
		fmt.Printf("%2d | %9.4f | %9.4f | %9.4f\n", iter, x0, x1, math.Abs(x1-x0))
		x0 = x1
		x1 = x0 - f(x0)/df(x0)
		iter++
	}
	fmt.Printf("Root: %.4f found in %d iterations\n", x1, iter)
	return x1, iter
}

// Метод простых итераций
func simpleIteration(x0 float64) (float64, int) {
	iter := 0
	x1 := phi(x0)
	fmt.Println("\nSIMPLE ITERATION METHOD")
	fmt.Printf("%2s | %9s | %9s | %9s\n", "N", "xₙ", "xₙ₊₁", "Δx")
	
	for math.Abs(x1-x0) > epsilon {
		fmt.Printf("%2d | %9.4f | %9.4f | %9.4f\n", iter, x0, x1, math.Abs(x1-x0))
		x0 = x1
		x1 = phi(x0)
		iter++
	}
	fmt.Printf("Root: %.4f found in %d iterations\n", x1, iter)
	return x1, iter
}

func main() {
	var roots []float64
	var iters [3]int

	// Метод половинного деления
	if root, iter, err := bisection(-1, 0); err == nil {
		roots = append(roots, root)
		iters[0] = iter
	} else {
		fmt.Println(err)
	}

	// Метод Ньютона
	root, iter := newton(-1)
	roots = append(roots, root)
	iters[1] = iter

	// Метод простых итераций
	root, iter = simpleIteration(-1)
	roots = append(roots, root)
	iters[2] = iter

	// Результаты
	fmt.Println("\nFOUND ROOTS:")
	for _, r := range roots {
		fmt.Printf("%.4f ", r)
	}
	
	fmt.Println("\n\nCONVERGENCE COMPARISON:")
	fmt.Printf("Bisection: %d iterations\n", iters[0])
	fmt.Printf("Newton:    %d iterations\n", iters[1])
	fmt.Printf("Iteration: %d iterations\n", iters[2])
}
