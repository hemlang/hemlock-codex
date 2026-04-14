package main

import (
	"encoding/json"
	"fmt"
)

type Config struct {
	Host           string `json:"host"`
	Port           int    `json:"port"`
	Debug          bool   `json:"debug"`
	LogLevel       string `json:"log_level"`
	MaxConnections int    `json:"max_connections"`
	Timeout        int    `json:"timeout"`
}

func prettyPrint(cfg Config) {
	data, _ := json.MarshalIndent(cfg, "", "  ")
	fmt.Println(string(data))
}

func mergeConfig(base Config, overrides map[string]interface{}) Config {
	result := base
	if v, ok := overrides["port"]; ok {
		result.Port = int(v.(float64))
	}
	if v, ok := overrides["host"]; ok {
		result.Host = v.(string)
	}
	if v, ok := overrides["debug"]; ok {
		result.Debug = v.(bool)
	}
	if v, ok := overrides["log_level"]; ok {
		result.LogLevel = v.(string)
	}
	if v, ok := overrides["max_connections"]; ok {
		result.MaxConnections = int(v.(float64))
	}
	if v, ok := overrides["timeout"]; ok {
		result.Timeout = int(v.(float64))
	}
	return result
}

func main() {
	defaults := Config{
		Host:           "localhost",
		Port:           8080,
		Debug:          false,
		LogLevel:       "info",
		MaxConnections: 100,
		Timeout:        30,
	}

	userConfigStr := `{"port": 3000, "debug": true, "log_level": "debug"}`
	var userOverrides map[string]interface{}
	json.Unmarshal([]byte(userConfigStr), &userOverrides)

	finalConfig := mergeConfig(defaults, userOverrides)

	fmt.Println("=== Default Config ===")
	prettyPrint(defaults)
	fmt.Println("=== User Overrides ===")
	userCfgData, _ := json.MarshalIndent(userOverrides, "", "  ")
	fmt.Println(string(userCfgData))
	fmt.Println("=== Final Config ===")
	prettyPrint(finalConfig)
}
