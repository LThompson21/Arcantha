#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // For glm::value_ptr
#include <iostream>

int main()
{
    // Test basic vector operations
    glm::vec3 vecA( 1.0f, 2.0f, 3.0f );
    glm::vec3 vecB( 4.0f, 5.0f, 6.0f );
    glm::vec3 vecSum = vecA + vecB;

    std::cout << "GLM Test:" << std::endl;
    std::cout << "Vector A: (" << vecA.x << ", " << vecA.y << ", " << vecA.z << ")" << std::endl;
    std::cout << "Vector B: (" << vecB.x << ", " << vecB.y << ", " << vecB.z << ")" << std::endl;
    std::cout << "Vector Sum (A + B): (" << vecSum.x << ", " << vecSum.y << ", " << vecSum.z << ")" << std::endl;

    // Test matrix creation and transformation
    glm::mat4 identityMatrix = glm::mat4( 1.0f ); // Identity matrix
    glm::mat4 translationMatrix = glm::translate( identityMatrix, glm::vec3( 10.0f, 0.0f, 0.0f ) );
    glm::mat4 rotationMatrix = glm::rotate( identityMatrix, glm::radians( 90.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
    glm::mat4 scaleMatrix = glm::scale( identityMatrix, glm::vec3( 2.0f, 2.0f, 2.0f ) );

    std::cout << "\nIdentity Matrix:\n";
    for ( int i = 0; i < 4; ++i )
    {
        for ( int j = 0; j < 4; ++j )
        {
            std::cout << identityMatrix[ j ][ i ] << "\t"; // GLM uses column-major order
        }
        std::cout << std::endl;
    }

    std::cout << "\nTranslation Matrix (10,0,0):\n";
    for ( int i = 0; i < 4; ++i )
    {
        for ( int j = 0; j < 4; ++j )
        {
            std::cout << translationMatrix[ j ][ i ] << "\t";
        }
        std::cout << std::endl;
    }

    // Test matrix-vector multiplication
    glm::vec4 originalVec( 1.0f, 0.0f, 0.0f, 1.0f ); // Homogeneous coordinate
    glm::vec4 transformedVec = translationMatrix * originalVec;

    std::cout << "\nTransformed vector (original (1,0,0,1) * translationMatrix): ("
        << transformedVec.x << ", " << transformedVec.y << ", " << transformedVec.z << ", " << transformedVec.w << ")" << std::endl;

    std::cout << "\nGLM test completed successfully." << std::endl;
    return 0;
}
