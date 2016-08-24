////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     BinaryOperationNode.h (features)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Node.h"
#include "ModelGraph.h"
#include "ModelTransformer.h"

// utilities
#include "Exception.h"
#include "TypeName.h"

// stl
#include <string>
#include <vector>

namespace nodes
{
    /// <summary> A node that performs a coordinatewise binary arithmetic operation on its inputs </summary>
    template <typename ValueType>
    class BinaryOperationNode : public model::Node
    {
    public:
        /// @name Input and Output Ports
        /// @{
        static constexpr const char* input1PortName = "input1";
        static constexpr const char* input2PortName = "input2";
        static constexpr const char* outputPortName = "output";
        const model::OutputPort<ValueType>& output = _output;
        /// @}

        /// <summary> Types of coordinatewise operations supported by this node type. </summary>
        enum class OperationType
        {
            none,
            add,
            subtract,
            coordinatewiseMultiply, // coordinatewise multiplication
            divide, // coordinatewise division
            logicalAnd,
            logicalOr,
            logicalXor
        };

        /// <summary> Default Constructor </summary>
        BinaryOperationNode();

        /// <summary> Constructor. </summary>
        ///
        /// <param name="input1"> The left-hand input of the arithmetic expression. </param>
        /// <param name="input2"> The right-hand input of the arithmetic expression. </param>
        /// <param name="operation"> The type of operation to perform. </param>
        BinaryOperationNode(const model::PortElements<ValueType>& input1, const model::PortElements<ValueType>& input2, OperationType operation);

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return utilities::GetCompositeTypeName<ValueType>("BinaryOperationNode"); }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        virtual std::string GetRuntimeTypeName() const override { return GetTypeName(); }

        /// <summary> Writes to a Serializer. </summary>
        ///
        /// <param name="serializer"> The serializer. </param>
        virtual void Serialize(utilities::Serializer& serializer) const override;

        /// <summary> Reads from a Deserializer. </summary>
        ///
        /// <param name="deserializer"> The deserializer. </param>
        /// <param name="context"> The serialization context. </param>
        virtual void Deserialize(utilities::Deserializer& serializer, utilities::SerializationContext& context) override;

        /// <summary> Makes a copy of this node in the graph being constructed by the transformer </summary>
        virtual void Copy(model::ModelTransformer& transformer) const override;

    protected:
        virtual void Compute() const override;

    private:
        template <typename Operation>
        std::vector<ValueType> ComputeOutput(Operation&& function) const;

        // Inputs
        model::InputPort<ValueType> _input1;
        model::InputPort<ValueType> _input2;

        // Output
        model::OutputPort<ValueType> _output;

        // Operation
        OperationType _operation;
    };
}

#include "../tcc/BinaryOperationNode.tcc"