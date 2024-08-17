
export const Commands = {
    init,
};

function init(device) {
    return {
        submit: (passes) =>  submit(device, passes)
    }
}

function submit(device, passes) {
    const commandEncoder = device.createCommandEncoder();

    passes.forEach(p => encodeRenderPass(commandEncoder, p));

    device.queue.submit([commandEncoder.finish()]);
}

export function encodeRenderPass(commandEncoder, config) {
    const { 
        descriptor,
        textureTargets,
        canvasTargets,
        commands
    } = config;


    descriptor.colorAttachments.forEach((c, i) => {
        const texture = textureTargets[i];
        const context = canvasTargets[i];
        
        if (context) {
            if (texture) {
                c.resolveTarget = context.getCurrentTexture().createView();
            } else {
                c.view = context.getCurrentTexture().createView();
            }
        }   
    });

    const renderPass = commandEncoder.beginRenderPass(descriptor);

    let indexedDraw = false;
    commands.forEach(d => {
        const { pipeline, mesh, uniforms, draw } = d;

        if (pipeline) {
            renderPass.setPipeline(pipeline.handle);
        }

        if (mesh) {
            const { vertices, indices } = mesh;
            vertices.forEach((b, i) => renderPass.setVertexBuffer(i, b.handle));
            if (indices) {
                renderPass.setIndexBuffer(indices.handle, indices.type);
                indexedDraw = true;
            } else {
                indexedDraw = false;
            }
        }

        if (uniforms) {
            uniforms.forEach((u, i) => renderPass.setBindGroup(i, u));
        }

        if (draw) {
            const { vertices, instances = 1 } = draw;
            if (indexedDraw) {
                renderPass.drawIndexed(vertices, instances);
            } else if (vertices) {
                renderPass.draw(vertices, instances);
            }
        }
    })
    
    renderPass.end();
}