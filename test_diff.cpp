#include <iostream>
#include <vector>
#include <chrono>

using namespace std::literals::chrono_literals;

#include "test_data.h"
#include "diff.h"

void test_diff()
{
    int right { 0 };
    int wrong { 0 };
    std::vector<DIFF::EditOp<int>> veo;
    auto start = std::chrono::high_resolution_clock::now();
#if 0
    for (int n = 1; n < 139; n += 2)
    {
        std::cout << "veo.clear();\n";
        std::cout << "std::cout << \"veo.clear();\\n\";\n";
        std::cout << "std::cout << \"(DIFF::diff(a" << n << ", a" << n + 1 << ", veo) != \" << DIFF::diff(a" << n << ", a" << n + 1 << ", veo) << \") ? ++wrong : ++right;\\n\" ;\n";
    }
#else
    veo.clear();
    (DIFF::diff(a1, a2, veo) != 26) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a3, a4, veo) != 26) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a5, a6, veo) != 24) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a7, a8, veo) != 20) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a9, a10, veo) != 18) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a11, a12, veo) != 17) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a13, a14, veo) != 17) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a15, a16, veo) != 15) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a17, a18, veo) != 23) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a19, a20, veo) != 20) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a21, a22, veo) != 17) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a23, a24, veo) != 16) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a25, a26, veo) != 16) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a27, a28, veo) != 27) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a29, a30, veo) != 21) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a31, a32, veo) != 21) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a33, a34, veo) != 27) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a35, a36, veo) != 24) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a37, a38, veo) != 24) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a39, a40, veo) != 23) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a41, a42, veo) != 19) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a43, a44, veo) != 24) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a45, a46, veo) != 22) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a47, a48, veo) != 16) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a49, a50, veo) != 16) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a51, a52, veo) != 21) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a53, a54, veo) != 22) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a55, a56, veo) != 22) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a57, a58, veo) != 22) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a59, a60, veo) != 17) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a61, a62, veo) != 17) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a63, a64, veo) != 15) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a65, a66, veo) != 13) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a67, a68, veo) != 11) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a69, a70, veo) != 21) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a71, a72, veo) != 18) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a73, a74, veo) != 18) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a75, a76, veo) != 16) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a77, a78, veo) != 13) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a79, a80, veo) != 19) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a81, a82, veo) != 19) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a83, a84, veo) != 16) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a85, a86, veo) != 24) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a87, a88, veo) != 21) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a89, a90, veo) != 18) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a91, a92, veo) != 15) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a93, a94, veo) != 16) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a95, a96, veo) != 15) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a97, a98, veo) != 17) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a99, a100, veo) != 14) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a101, a102, veo) != 19) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a103, a104, veo) != 17) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a105, a106, veo) != 16) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a107, a108, veo) != 15) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a109, a110, veo) != 12) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a111, a112, veo) != 22) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a113, a114, veo) != 20) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a115, a116, veo) != 19) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a117, a118, veo) != 18) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a119, a120, veo) != 18) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a121, a122, veo) != 15) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a123, a124, veo) != 16) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a125, a126, veo) != 15) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a127, a128, veo) != 13) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a129, a130, veo) != 13) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a131, a132, veo) != 9) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a133, a134, veo) != 10) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a135, a136, veo) != 9) ? ++wrong : ++right;
    veo.clear();
    (DIFF::diff(a137, a138, veo) != 2) ? ++wrong : ++right;
#endif
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "test_diff :  " << (end - start) / 1us << "us\n";
    std::cout << "right = " << right << ", wrong = " << wrong << "\n";
}