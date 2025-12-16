// author: ripley white <ripley@ripples.gay>
// "what if we need a windows 95 key, huh? not like we're able to fucking buy them anymore. capitalist pig."
// :3

package main

import (
	"fmt"
	"math/rand/v2"
)

const MAX_ARR_SIZE = 14282

func pad_num(i int, final_len int) string {
	// hack: never had to deal with sprintf's before. probs a better way to do this.
	return fmt.Sprintf("%0*d", final_len, i)
}

func rnd(minVal, maxVal int) int {
	// yeah no don't even ask this is just cursed.
	return rand.N(maxVal-minVal) + minVal
}

func main() {
	fmt.Println("calculating..")

	arr := make([]string, 0)

	for i := range 100000 {
		if len(arr) >= MAX_ARR_SIZE {
			break
		}

		padded := pad_num(i, 5)
		sum := 0

		for _, r := range padded {
			// this is so cursed (rune -> int conv)
			sum += int(r - '0')
		}

		if sum%7 == 0 {
			arr = append(arr, padded)
		}
	}

	one := pad_num(rnd(1, 366), 3)
	two := pad_num(rnd(95, 99), 2)
	three := arr[rnd(0, len(arr))]
	four := arr[rnd(0, len(arr))]

	fmt.Printf("%s%s-OEM-00%s-%s\n", one, two, three, four)
}
