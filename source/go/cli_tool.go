package main

import "fmt"

type Config struct {
	verbose bool
	output  string
	format  string
	count   int
}

func parseOption(key, value string, cfg *Config) {
	switch key {
	case "--verbose", "-v":
		cfg.verbose = true
	case "--output", "-o":
		cfg.output = value
	case "--format", "-f":
		cfg.format = value
	case "--count", "-n":
		n := 0
		fmt.Sscanf(value, "%d", &n)
		cfg.count = n
	}
}

func main() {
	toolName := "hemlock-tool"
	version := "1.0.0"

	cfg := &Config{
		verbose: false,
		output:  "stdout",
		format:  "text",
		count:   10,
	}

	simulatedArgs := [][2]string{
		{"--verbose", ""},
		{"--output", "result.txt"},
		{"--format", "json"},
		{"--count", "25"},
	}

	for _, arg := range simulatedArgs {
		parseOption(arg[0], arg[1], cfg)
	}

	fmt.Printf("%s v%s\n", toolName, version)
	fmt.Println("Parsed configuration:")
	fmt.Printf("  verbose: %v\n", cfg.verbose)
	fmt.Printf("  output:  %s\n", cfg.output)
	fmt.Printf("  format:  %s\n", cfg.format)
	fmt.Printf("  count:   %d\n", cfg.count)
	fmt.Println("Ready to process.")
}
