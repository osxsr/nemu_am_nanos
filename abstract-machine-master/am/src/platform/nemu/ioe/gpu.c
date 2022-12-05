#include <am.h>
#include <nemu.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

AM_GPU_CONFIG_T config;

void __am_gpu_init() {
  int i;
  uint32_t hei_wei = inl(VGACTL_ADDR);
  uint32_t w = config.width = hei_wei >> 16;  
  uint32_t h = config.height = hei_wei & 0xffff;  
  


  int n_d = 1;
  int tmp_d = hei_wei;
  while(tmp_d>9){
    n_d*=10;
    tmp_d/=10;
  }
  while(n_d){
    if(hei_wei){
      putch('0' + hei_wei/n_d);
      hei_wei=hei_wei%n_d;
    }
    else
      putch('0');
    n_d/=10;
  }

  putch(' ');
  n_d = 1;
  tmp_d = w;
  while(tmp_d>9){
    n_d*=10;
    tmp_d/=10;
  }
  while(n_d){
    if(h){
      putch('0' + h/n_d);
      h=h%n_d;
    }
    else
      putch('0');
    n_d/=10;
  }

  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  for (i = 0; i < w * h; i ++) fb[i] = i;
  outl(SYNC_ADDR, 1);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
    config.present = true;
    config.has_accel = false;
    config.vmemsz = 0;
    cfg=&config;
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {

  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
  uint32_t *fb = (uint32_t *)(uintptr_t)(FB_ADDR+ctl->y*config.width+ctl->x);
  for(int i=0;i<ctl->h;i++)
  {
    for(int j=0;j<ctl->w;j++){
      if(i+ctl->y < config.height && j+ctl->x < config.width)
      {
        *fb = *(uint32_t*)ctl->pixels+i*ctl->w+j;
      }
    }
    fb += (config.width - ctl->w) ;
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
