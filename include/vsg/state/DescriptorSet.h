#pragma once

/* <editor-fold desc="MIT License">

Copyright(c) 2018 Robert Osfield

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

</editor-fold> */

#include <vsg/state/Descriptor.h>
#include <vsg/state/DescriptorSetLayout.h>

namespace vsg
{

    class DescriptorSet_Implementation;

    class VSG_DECLSPEC DescriptorSet : public Inherit<Object, DescriptorSet>
    {
    public:
        DescriptorSet();
        DescriptorSet(ref_ptr<DescriptorSetLayout> in_descriptorSetLayout, const Descriptors& in_descriptors);

        /// VkDescriptorSetAllocateInfo settings
        ref_ptr<DescriptorSetLayout> setLayout;
        Descriptors descriptors;

        int compare(const Object& rhs_object) const override;

        template<class N, class V>
        static void t_traverse(N& ds, V& visitor)
        {
            if (ds.setLayout) ds.setLayout->accept(visitor);
            for (auto& descriptor : ds.descriptors) descriptor->accept(visitor);
        }

        void traverse(Visitor& visitor) override { t_traverse(*this, visitor); }
        void traverse(ConstVisitor& visitor) const override { t_traverse(*this, visitor); }

        void read(Input& input) override;
        void write(Output& output) const override;

        // compile the Vulkan object, context parameter used for Device
        void compile(Context& context);

        // remove the local reference to the Vulkan implementation
        void release(uint32_t deviceID);
        void release();

        VkDescriptorSet vk(uint32_t deviceID) const;

    protected:
        virtual ~DescriptorSet();

        vk_buffer<ref_ptr<DescriptorSet_Implementation>> _implementation;
    };
    VSG_type_name(vsg::DescriptorSet);

    using DescriptorSets = std::vector<ref_ptr<DescriptorSet>>;

} // namespace vsg
