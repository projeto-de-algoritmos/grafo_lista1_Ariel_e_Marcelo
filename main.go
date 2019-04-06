package main

import (
	"fmt"
	"os/exec"
)

func main() {

	out, err := exec.Command("./path.sh").Output()
	if err != nil {
		fmt.Printf("I found some error to run the PATH: %s", err)
	} else {
		fmt.Println("\nCommand Successfully Executed")
	}
	output := string(out[:])
	fmt.Println(output)
	out, err = exec.Command("./travel.sh").Output()
	if err != nil {
		fmt.Printf("I found some error to run the TRAVEL: %s", err)
	} else {
		fmt.Println("\nCommand Successfully Executed")
	}
	output = string(out[:])
	fmt.Println(output)
	out, err = exec.Command("./master_run.sh").Output()
	if err != nil {
		fmt.Printf("I found some error to run the MASTER: %s", err)
	} else {
		fmt.Println("\nCommand Successfully Executed")
	}
	output = string(out[:])
	fmt.Println(output)
}
