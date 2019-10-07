/*
 ==============================================================================
    Copyright (c) 2019 Foleys Finest Audio Ltd. - Daniel Walz
    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
    IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
    INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
    OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
    OF THE POSSIBILITY OF SUCH DAMAGE.
 ==============================================================================
 */

namespace foleys
{


EditorPanels::EditorPanels (MagicBuilder& builderToControl)
  : builder (builderToControl),
    treeEditor (builderToControl),
    propertiesEditor (builderToControl)
{
    treeEditor.onSelectionChanged = [&] (juce::ValueTree& ref)
    {
        setSelectedNode (ref);
    };

    addAndMakeVisible (treeEditor);
    addAndMakeVisible (resizer);
    addAndMakeVisible (propertiesEditor);

    resizeManager.setItemLayout (0, 1, -1.0, -0.6);
    resizeManager.setItemLayout (1, 6, 6, 6);
    resizeManager.setItemLayout (2, 1, -1.0, -0.4);
}

void EditorPanels::setSelectedNode (const juce::ValueTree& node)
{
    treeEditor.setSelectedNode (node);
    propertiesEditor.setNodeToEdit (node);
    builder.setSelectedNode (node);
}

void EditorPanels::update()
{
    treeEditor.updateTree();
    propertiesEditor.setStyle (builder.getStylesheet().getCurrentStyle());
}

void EditorPanels::paint (juce::Graphics& g)
{
    g.fillAll (EditorColours::background);
}

void EditorPanels::resized()
{
    auto bounds = getLocalBounds();

    juce::Component* comps[] = { &treeEditor, &resizer, &propertiesEditor };
    resizeManager.layOutComponents (comps, 3,
                                    bounds.getX(),
                                    bounds.getY(),
                                    bounds.getWidth(),
                                    bounds.getHeight(),
                                    true, true);
}


} // namespace foleys