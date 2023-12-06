package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

func main() {

	file, _ := os.Open("input.txt")
	defer file.Close()

	times := make([]float64, 0, 20)
	distances := make([]float64, 0, 20)

    var sb strings.Builder
    var tm, dst float64

	scanner := bufio.NewScanner(file)
	scanner.Scan()
	in := strings.Split(scanner.Text(), " ")
	for _, k := range in {
		num, err := strconv.Atoi(k)
		if err != nil || num == 0 {
			continue
		}
        sb.WriteString(k)
		times = append(times, float64(num))
	}
    tmp, _ := strconv.Atoi(sb.String())
    tm = float64(tmp)
    sb.Reset()
	scanner.Scan()
	in = strings.Split(scanner.Text(), " ")
	for _, k := range in {
		num, err := strconv.Atoi(k)
		if err != nil || num == 0 {
			continue
		}
        sb.WriteString(k)
		distances = append(distances, float64(num))
	}
    tmp, _ = strconv.Atoi(sb.String())
    dst = float64(tmp)

    // first part : 
    sum := 1
    for i := range times {
        sum *= calculate(times[i], distances[i])
    }
    fmt.Println(sum)

    // second part :
    fmt.Println(calculate(tm, dst))


	return
}

func calculate(time, distance float64) int {
	x1 := math.Ceil((time - math.Sqrt(time*time-4*distance)) / 2)
	x2 := math.Floor((time + math.Sqrt(time*time-4*distance)) / 2)
	offset := 0.0
	if (x1 * (time - x1)) == distance {
		offset++
	}
	if (x2 * (time - x2)) == distance {
		offset++
	}
	return int(math.Round((x2 - x1) + 1 - offset))
}
