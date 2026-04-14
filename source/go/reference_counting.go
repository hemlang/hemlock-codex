package main

import "fmt"

// Manual reference counting simulation
type RCObject struct {
	refcount int
	data     int
}

func rcNew(data int) *RCObject {
	obj := &RCObject{refcount: 1, data: data}
	fmt.Printf("created obj(data=%d, refcount=1)\n", data)
	return obj
}

func rcRetain(obj *RCObject) *RCObject {
	obj.refcount++
	fmt.Printf("retain obj(data=%d, refcount=%d)\n", obj.data, obj.refcount)
	return obj
}

func rcRelease(obj *RCObject) *RCObject {
	obj.refcount--
	if obj.refcount == 0 {
		fmt.Printf("release obj(data=%d, refcount=0) -> freed\n", obj.data)
		return nil
	}
	fmt.Printf("release obj(data=%d, refcount=%d)\n", obj.data, obj.refcount)
	return obj
}

func main() {
	fmt.Println("--- create object ---")
	a := rcNew(42)

	fmt.Println("--- share with b ---")
	b := rcRetain(a)

	fmt.Println("--- share with c ---")
	c := rcRetain(a)

	fmt.Printf("data: %d, refcount: %d\n", a.data, a.refcount)

	fmt.Println("--- release a ---")
	a = rcRelease(a)

	fmt.Println("--- release b ---")
	b = rcRelease(b)

	fmt.Println("--- release c (last ref, should free) ---")
	c = rcRelease(c)

	_ = a
	_ = b
	_ = c
}
