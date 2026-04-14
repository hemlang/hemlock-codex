package main

import "fmt"

type Request struct {
	method string
	path   string
}

type Response struct {
	status int
	body   string
	method string
	path   string
}

func serverHandler(req Request) Response {
	var body string
	status := 200
	switch req.path {
	case "/":
		body = "Hello, World!"
	case "/about":
		body = "About Page"
	default:
		status = 404
		body = "Not Found"
	}
	return Response{status: status, body: body, method: req.method, path: req.path}
}

func main() {
	requestCh := make(chan Request, 10)
	responseCh := make(chan Response, 10)
	done := make(chan struct{})

	// Server goroutine
	go func() {
		for i := 0; i < 3; i++ {
			req := <-requestCh
			res := serverHandler(req)
			responseCh <- res
		}
	}()

	// Client goroutine
	go func() {
		requests := []Request{
			{method: "GET", path: "/"},
			{method: "GET", path: "/about"},
			{method: "GET", path: "/missing"},
		}
		for _, req := range requests {
			requestCh <- req
			res := <-responseCh
			fmt.Printf("[simulated] %s %s -> %d %s\n", res.method, res.path, res.status, res.body)
		}
		close(done)
	}()

	<-done
}
