use std::alloc::{alloc, dealloc, Layout};

const COUNT: usize = 5;

struct SoA {
    xs: *mut f64,
    ys: *mut f64,
    zs: *mut f64,
}

impl SoA {
    fn new() -> Self {
        let layout = Layout::array::<f64>(COUNT).unwrap();
        unsafe {
            SoA {
                xs: alloc(layout) as *mut f64,
                ys: alloc(layout) as *mut f64,
                zs: alloc(layout) as *mut f64,
            }
        }
    }

    unsafe fn set_point(&mut self, i: usize, x: f64, y: f64, z: f64) {
        *self.xs.add(i) = x;
        *self.ys.add(i) = y;
        *self.zs.add(i) = z;
    }

    unsafe fn get_x(&self, i: usize) -> f64 { *self.xs.add(i) }
    unsafe fn get_y(&self, i: usize) -> f64 { *self.ys.add(i) }
    unsafe fn get_z(&self, i: usize) -> f64 { *self.zs.add(i) }

    unsafe fn distance(&self, i: usize) -> f64 {
        let x = self.get_x(i);
        let y = self.get_y(i);
        let z = self.get_z(i);
        (x * x + y * y + z * z).sqrt()
    }
}

impl Drop for SoA {
    fn drop(&mut self) {
        let layout = Layout::array::<f64>(COUNT).unwrap();
        unsafe {
            dealloc(self.xs as *mut u8, layout);
            dealloc(self.ys as *mut u8, layout);
            dealloc(self.zs as *mut u8, layout);
        }
    }
}

fn fmt_f64(v: f64) -> String {
    // Match Hemlock output format
    if v == v.floor() && v.abs() < 1e15 {
        format!("{}", v as i64 as f64)
    } else {
        format!("{}", v)
    }
}

fn main() {
    let mut soa = SoA::new();
    let points = [(1.0, 0.0, 0.0), (0.0, 2.0, 0.0), (0.0, 0.0, 3.0), (1.0, 1.0, 1.0), (3.0, 4.0, 0.0)];
    unsafe {
        for (i, &(x, y, z)) in points.iter().enumerate() {
            soa.set_point(i, x, y, z);
        }
        for i in 0..COUNT {
            let x = soa.get_x(i);
            let y = soa.get_y(i);
            let z = soa.get_z(i);
            let d = soa.distance(i);
            println!("point {}: ({}, {}, {}) distance = {}", i, fmt_f64(x), fmt_f64(y), fmt_f64(z), fmt_f64(d));
        }
    }
    drop(soa);
    println!("all arrays freed");
}
