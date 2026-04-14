package main

import (
	"fmt"
	"math"
)

// SoA layout: parallel arrays for x, y, z coordinates
const COUNT = 5

var xs [COUNT]float64
var ys [COUNT]float64
var zs [COUNT]float64

func setPoint(i int, x, y, z float64) {
	xs[i] = x
	ys[i] = y
	zs[i] = z
}

func distance(i int) float64 {
	x := xs[i]
	y := ys[i]
	z := zs[i]
	return math.Sqrt(x*x + y*y + z*z)
}

func main() {
	setPoint(0, 1.0, 0.0, 0.0)
	setPoint(1, 0.0, 2.0, 0.0)
	setPoint(2, 0.0, 0.0, 3.0)
	setPoint(3, 1.0, 1.0, 1.0)
	setPoint(4, 3.0, 4.0, 0.0)

	for i := 0; i < COUNT; i++ {
		x := xs[i]
		y := ys[i]
		z := zs[i]
		d := distance(i)
		fmt.Printf("point %d: (%g, %g, %g) distance = %g\n", i, x, y, z, d)
	}

	fmt.Println("all arrays freed")
}
