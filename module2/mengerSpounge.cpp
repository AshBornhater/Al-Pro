/*
 * ╔══════════════════════════════════════════════════════════════════╗
 * ║       3D CINEMATIC MENGER SPONGE TERMINAL RENDERER              ║
 * ║       Teknik: Ray Marching + ASCII Shading + Rotation Matrix    ║
 * ║       Camera: Cinematic zoom-in ke lubang fraktal               ║
 * ╚══════════════════════════════════════════════════════════════════╝
 *
 * Compile: g++ -O2 -o menger menger_sponge.cpp -lm
 * Run    : ./menger
 */

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <unistd.h>   // usleep
#include <csignal>

// ─── Terminal Size ──────────────────────────────────────────────────
static const int W = 120;   // lebar terminal
static const int H = 50;    // tinggi terminal

// ─── ASCII Gradient (gelap → terang) ────────────────────────────────
// 10 level intensitas cahaya
static const char SHADE[] = " .:+*=%#@";
static const int  NSHADE   = 9;   // strlen(SHADE)

// ─── Struct Vec3 ─────────────────────────────────────────────────────
struct Vec3 {
    float x, y, z;
    Vec3(float x=0,float y=0,float z=0): x(x),y(y),z(z){}
    Vec3 operator+(const Vec3& b) const { return {x+b.x, y+b.y, z+b.z}; }
    Vec3 operator-(const Vec3& b) const { return {x-b.x, y-b.y, z-b.z}; }
    Vec3 operator*(float t)       const { return {x*t,   y*t,   z*t  }; }
    float dot(const Vec3& b)      const { return x*b.x + y*b.y + z*b.z; }
    float len()                   const { return std::sqrt(dot(*this));  }
    Vec3  normalize()             const { float l=len(); return {x/l,y/l,z/l}; }
};

// ─── Rotation Matrix 3×3 (disimpan row-major) ───────────────────────
struct Mat3 {
    float m[3][3];
    Vec3 apply(const Vec3& v) const {
        return {
            m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z,
            m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z,
            m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z
        };
    }
};

// Rotation X-axis
Mat3 rotX(float a){
    float c=cos(a), s=sin(a);
    return {{{1,0,0},{0,c,-s},{0,s,c}}};
}
// Rotation Y-axis
Mat3 rotY(float a){
    float c=cos(a), s=sin(a);
    return {{{c,0,s},{0,1,0},{-s,0,c}}};
}
// Rotation Z-axis
Mat3 rotZ(float a){
    float c=cos(a), s=sin(a);
    return {{{c,-s,0},{s,c,0},{0,0,1}}};
}
// Kombinasi dua matriks
Mat3 mul(const Mat3& A, const Mat3& B){
    Mat3 R={};
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            for(int k=0;k<3;k++)
                R.m[i][j] += A.m[i][k]*B.m[k][j];
    return R;
}

// ─── SDF: Menger Sponge ──────────────────────────────────────────────
// Signed Distance Function rekursif untuk Menger Sponge
// level = jumlah iterasi rekursi (1–4 cukup untuk terminal)
float sdBox(Vec3 p, float r){
    float dx = std::fabs(p.x)-r;
    float dy = std::fabs(p.y)-r;
    float dz = std::fabs(p.z)-r;
    float ex = std::fmax(dx,0.f);
    float ey = std::fmax(dy,0.f);
    float ez = std::fmax(dz,0.f);
    return std::sqrt(ex*ex+ey*ey+ez*ez)
         + std::fmin(std::fmax(dx,std::fmax(dy,dz)),0.f);
}

// SDF "cross" (3 sumbu persegi berlubang)
float sdCross(Vec3 p, float r){
    float inf = 1e9f;
    float d1 = std::fmax(std::fabs(p.y)-r, std::fmax(std::fabs(p.z)-r, -inf));
    float d2 = std::fmax(std::fabs(p.x)-r, std::fmax(std::fabs(p.z)-r, -inf));
    float d3 = std::fmax(std::fabs(p.x)-r, std::fmax(std::fabs(p.y)-r, -inf));
    // redefine lebih tepat
    float a = std::fmax(std::fabs(p.x)-r, std::fabs(p.y)-r);
    float b = std::fmax(std::fabs(p.y)-r, std::fabs(p.z)-r);
    float c2= std::fmax(std::fabs(p.x)-r, std::fabs(p.z)-r);
    (void)d1; (void)d2; (void)d3;
    return std::fmin(a, std::fmin(b, c2));
}

float mengerSponge(Vec3 p, int iter){
    float d = sdBox(p, 1.f);          // kubus luar
    float s = 1.f;
    for(int i=0; i<iter; i++){
        // fold / repetisi koordinat ke [0,1]
        Vec3 a;
        a.x = std::fmod(std::fabs(p.x)*s, 1.f)*2.f - 1.f;
        a.y = std::fmod(std::fabs(p.y)*s, 1.f)*2.f - 1.f;
        a.z = std::fmod(std::fabs(p.z)*s, 1.f)*2.f - 1.f;
        s *= 3.f;
        // kurangi dengan cross-bar di tiap skala
        float c = sdCross(a, 1.f/3.f) / s;
        d = std::fmax(d, -c);         // CSG: kubus – cross
    }
    return d;
}

// ─── Normal via Gradient Numerik ────────────────────────────────────
Vec3 calcNormal(Vec3 p, int iter){
    const float eps = 0.002f;
    return Vec3(
        mengerSponge({p.x+eps,p.y,p.z},iter) - mengerSponge({p.x-eps,p.y,p.z},iter),
        mengerSponge({p.x,p.y+eps,p.z},iter) - mengerSponge({p.x,p.y-eps,p.z},iter),
        mengerSponge({p.x,p.y,p.z+eps},iter) - mengerSponge({p.x,p.y,p.z-eps},iter)
    ).normalize();
}

// ─── Ray Marching ────────────────────────────────────────────────────
bool rayMarch(Vec3 ro, Vec3 rd, int iter, float& tHit){
    float t = 0.1f;
    for(int i=0; i<96; i++){
        Vec3 p = ro + rd*t;
        float d = mengerSponge(p, iter);
        if(d < 0.001f){ tHit = t; return true; }
        if(t > 20.f)  { return false; }
        t += d * 0.7f;  // relaxed step untuk kestabilan
    }
    return false;
}

// ─── Render Buffer ───────────────────────────────────────────────────
char  buf [H][W+1];
float zbuf[H][W];

void clearBuf(){
    for(int y=0;y<H;y++){
        for(int x=0;x<W;x++){
            buf[y][x]  = ' ';
            zbuf[y][x] = 1e9f;
        }
        buf[y][W] = '\0';
    }
}

// ─── Main Render Frame ───────────────────────────────────────────────
void renderFrame(float angX, float angY, float angZ,
                 float camDist, int iter)
{
    // Matriks rotasi gabungan (Y × X × Z)
    Mat3 R = mul(rotY(angY), mul(rotX(angX), rotZ(angZ)));

    // Sumber cahaya (world-space) — sudut sinematik
    Vec3 lightDir = Vec3(1.2f, 2.f, -0.8f).normalize();

    // Aspect ratio koreksi (karakter terminal lebih tinggi dari lebar)
    const float aspect = (float)W / (float)H * 0.45f;
    const float fov    = 1.0f;    // tangent setengah sudut pandang

    for(int py=0; py<H; py++){
        for(int px=0; px<W; px++){
            // NDC [-1,1]
            float u = (2.f*(px+0.5f)/(float)W - 1.f) * aspect * fov;
            float v = (1.f - 2.f*(py+0.5f)/(float)H) * fov;

            // Ray di kamera-space, lalu rotasikan ke world-space
            Vec3 rd = R.apply(Vec3(u, v, -1.f).normalize());
            Vec3 ro = R.apply(Vec3(0,0, camDist));  // posisi kamera

            float tHit;
            if(rayMarch(ro, rd, iter, tHit)){
                Vec3 hitPos = ro + rd*tHit;
                Vec3 normal  = calcNormal(hitPos, iter);

                // ── Diffuse Lighting (Lambertian) ──
                float diff = std::fmax(0.f, normal.dot(lightDir));

                // ── Specular (Phong) ──
                Vec3 viewDir = (ro - hitPos).normalize();
                Vec3 reflDir = normal * (2.f*normal.dot(lightDir)) - lightDir;
                float spec   = std::pow(std::fmax(0.f, reflDir.dot(viewDir)), 16.f);

                // ── Ambient Occlusion sederhana (slot rekursi) ──
                float ao     = 1.f - (float)(iter) * 0.08f;

                // ── Gabungkan intensitas ──
                float intensity = (0.15f + 0.65f*diff + 0.25f*spec) * ao;
                intensity = std::fmax(0.f, std::fmin(1.f, intensity));

                // ── Pilih karakter ASCII ──
                int idx = (int)(intensity * (NSHADE-1));
                buf[py][px] = SHADE[idx];
                zbuf[py][px] = tHit;
            }
        }
    }
}

// ─── Print Frame ke Terminal ─────────────────────────────────────────
void printFrame(int frame, float angY, float camDist){
    // Pindahkan kursor ke atas (ANSI escape)
    if(frame > 0) printf("\033[%dA", H+3);

    // Border atas
    printf("\033[1;36m");  // cyan bold
    printf("┌");
    for(int i=0;i<W;i++) printf("─");
    printf("┐\n");

    for(int y=0;y<H;y++){
        printf("│");
        // Warna berdasarkan karakter (sinematik gradient)
        for(int x=0;x<W;x++){
            char c = buf[y][x];
            if(c == '@' || c == '#')      printf("\033[1;37m"); // putih terang
            else if(c == '%' || c == '*') printf("\033[0;37m"); // putih
            else if(c == '=' || c == '+') printf("\033[0;36m"); // cyan
            else if(c == '-' || c == ':') printf("\033[0;34m"); // biru
            else                          printf("\033[0;30m"); // abu gelap
            printf("%c", c);
        }
        printf("\033[1;36m│\n");
    }

    // Border bawah + info HUD
    printf("└");
    for(int i=0;i<W;i++) printf("─");
    printf("┘\n");
    printf("\033[0m");  // reset warna

    printf("\033[0;33m");  // kuning untuk HUD
    printf("  ◈ Menger Sponge │ Frame:%4d │ Rot: %.2frad │ Cam: %.2f │ Iter: 3  \n",
           frame, angY, camDist);
    printf("\033[0m");
}

// ─── Sinyal handler untuk keluar bersih ─────────────────────────────
static volatile bool running = true;
void handleSigint(int){ running = false; }

// ─── MAIN ────────────────────────────────────────────────────────────
int main(){
    signal(SIGINT, handleSigint);

    // Sembunyikan kursor
    printf("\033[?25l");
    // Clear screen
    printf("\033[2J\033[H");

    const int   ITER       = 3;      // level rekursi Menger Sponge
    const float ROT_SPEED  = 0.025f; // kecepatan rotasi (rad/frame)
    const float ZOOM_SPEED = 0.008f; // kecepatan zoom
    const float CAM_NEAR   = 1.8f;   // jarak kamera terdekat (zoom in)
    const float CAM_FAR    = 4.5f;   // jarak kamera terjauh

    float angX    = 0.4f;   // miring sedikit agar tampak 3D
    float angY    = 0.f;
    float angZ    = 0.15f;
    float camDist = CAM_FAR;
    bool  zoomIn  = true;
    int   frame   = 0;

    while(running){
        clearBuf();
        renderFrame(angX, angY, angZ, camDist, ITER);
        printFrame(frame, angY, camDist);

        // ── Update rotasi ──
        angY += ROT_SPEED;
        angX += ROT_SPEED * 0.31f;   // rotasi sumbu X lebih lambat
        angZ += ROT_SPEED * 0.17f;   // sedikit twist

        // ── Cinematic Camera: zoom in/out ──
        if(zoomIn){
            camDist -= ZOOM_SPEED;
            if(camDist <= CAM_NEAR){ camDist = CAM_NEAR; zoomIn = false; }
        } else {
            camDist += ZOOM_SPEED;
            if(camDist >= CAM_FAR ){ camDist = CAM_FAR;  zoomIn = true;  }
        }

        frame++;

        // ~30 fps
        usleep(33000);
    }

    // Tampilkan kursor kembali
    printf("\033[?25h");
    printf("\n\033[0;32mRenderer dihentikan. Terima kasih!\033[0m\n");
    return 0;
}