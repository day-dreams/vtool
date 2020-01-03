package internal

import (
	"fmt"
	"os"
	"os/signal"
	"syscall"
	"time"
)

type NopRunnable struct {
}

func listenSig() {
	sigs := make(chan os.Signal, 1)
	signal.Notify(sigs, syscall.SIGKILL, syscall.SIGTERM)
	for {
		sig := <-sigs
		fmt.Println("sig recved:%+v \n", sig.String())
		os.Exit(2)
	}
}

func (n NopRunnable) Run() {
	go listenSig()
	for {
		fmt.Printf("hello world. %v\n", time.Now())
		time.Sleep(time.Second)
	}
}
