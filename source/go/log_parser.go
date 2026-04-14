package main

import (
	"fmt"
	"strings"
)

func extractLevel(line string) string {
	if strings.Contains(line, "[INFO]") {
		return "INFO"
	}
	if strings.Contains(line, "[WARN]") {
		return "WARN"
	}
	if strings.Contains(line, "[ERROR]") {
		return "ERROR"
	}
	if strings.Contains(line, "[DEBUG]") {
		return "DEBUG"
	}
	return "UNKNOWN"
}

func extractTimestamp(line string) string {
	if len(line) >= 19 {
		return line[:19]
	}
	return line
}

func extractMessage(line string) string {
	parts := strings.SplitN(line, "] ", 2)
	if len(parts) > 1 {
		return parts[1]
	}
	return line
}

func main() {
	logs := []string{
		"2024-01-15 08:30:12 [INFO] Application started",
		"2024-01-15 08:30:15 [INFO] Loading configuration",
		"2024-01-15 08:30:16 [WARN] Config file not found, using defaults",
		"2024-01-15 08:31:00 [INFO] Processing 150 records",
		"2024-01-15 08:31:05 [ERROR] Failed to parse record #42",
		"2024-01-15 08:31:10 [WARN] Retrying failed operation",
		"2024-01-15 08:31:15 [INFO] Processing complete",
		"2024-01-15 08:31:20 [INFO] Shutting down",
	}

	infoCount := 0
	warnCount := 0
	errorCount := 0

	fmt.Println("=== Log Analysis ===")
	for _, line := range logs {
		level := extractLevel(line)
		switch level {
		case "INFO":
			infoCount++
		case "WARN":
			warnCount++
		case "ERROR":
			errorCount++
		}
	}

	fmt.Printf("Total lines: %d\n", len(logs))
	fmt.Printf("INFO: %d\n", infoCount)
	fmt.Printf("WARN: %d\n", warnCount)
	fmt.Printf("ERROR: %d\n", errorCount)

	fmt.Println("\n=== Error Details ===")
	for _, line := range logs {
		if strings.Contains(line, "[ERROR]") {
			fmt.Printf("  %s: %s\n", extractTimestamp(line), extractMessage(line))
		}
	}
}
